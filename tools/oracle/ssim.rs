use std::env;
use std::fs;
use std::io::{self, Read};
use std::path::{Path, PathBuf};

struct Image {
    width: usize,
    height: usize,
    pixels: Vec<u8>,
}

fn read_token<'a>(data: &'a [u8], cursor: &mut usize) -> Result<&'a [u8], String> {
    while *cursor < data.len() && data[*cursor].is_ascii_whitespace() {
        *cursor += 1;
    }
    let start = *cursor;
    while *cursor < data.len() && !data[*cursor].is_ascii_whitespace() {
        *cursor += 1;
    }
    if start == *cursor {
        return Err("truncated PPM header".into());
    }
    Ok(&data[start..*cursor])
}

fn read_ppm(path: &Path) -> Result<Image, String> {
    let data = fs::read(path).map_err(|error| format!("{}: {error}", path.display()))?;
    let mut cursor = 0;
    if read_token(&data, &mut cursor)? != b"P6" {
        return Err(format!("{}: expected binary PPM", path.display()));
    }
    let width = std::str::from_utf8(read_token(&data, &mut cursor)?)
        .map_err(|error| error.to_string())?.parse::<usize>()
        .map_err(|error| error.to_string())?;
    let height = std::str::from_utf8(read_token(&data, &mut cursor)?)
        .map_err(|error| error.to_string())?.parse::<usize>()
        .map_err(|error| error.to_string())?;
    if read_token(&data, &mut cursor)? != b"255" {
        return Err(format!("{}: expected 8-bit PPM", path.display()));
    }
    if cursor >= data.len() || !data[cursor].is_ascii_whitespace() {
        return Err(format!("{}: malformed PPM header", path.display()));
    }
    cursor += 1;
    let expected = width * height * 3;
    if data.len() - cursor != expected {
        return Err(format!("{}: expected {expected} pixel bytes, got {}",
                           path.display(), data.len() - cursor));
    }
    Ok(Image { width, height, pixels: data[cursor..].to_vec() })
}

fn luminance(pixels: &[u8], offset: usize) -> f64 {
    0.2126 * pixels[offset] as f64
        + 0.7152 * pixels[offset + 1] as f64
        + 0.0722 * pixels[offset + 2] as f64
}

fn mean(values: &[f64]) -> f64 {
    values.iter().sum::<f64>() / values.len() as f64
}

fn image_ssim(left: &Image, right: &Image) -> Result<f64, String> {
    if left.width != right.width || left.height != right.height {
        return Err("image dimensions differ".into());
    }
    let c1 = (0.01_f64 * 255.0).powi(2);
    let c2 = (0.03_f64 * 255.0).powi(2);
    let mut scores = Vec::new();
    let mut a = Vec::with_capacity(64);
    let mut b = Vec::with_capacity(64);
    for top in (0..left.height).step_by(8) {
        for x0 in (0..left.width).step_by(8) {
            a.clear();
            b.clear();
            for y in top..usize::min(top + 8, left.height) {
                for x in x0..usize::min(x0 + 8, left.width) {
                    let offset = (y * left.width + x) * 3;
                    a.push(luminance(&left.pixels, offset));
                    b.push(luminance(&right.pixels, offset));
                }
            }
            let count = a.len() as f64;
            let mean_a = mean(&a);
            let mean_b = mean(&b);
            let variance_a =
                a.iter().map(|value| (value - mean_a).powi(2)).sum::<f64>() / count;
            let variance_b =
                b.iter().map(|value| (value - mean_b).powi(2)).sum::<f64>() / count;
            let covariance = a.iter().zip(b.iter())
                .map(|(x, y)| (x - mean_a) * (y - mean_b))
                .sum::<f64>() / count;
            scores.push(((2.0 * mean_a * mean_b + c1) * (2.0 * covariance + c2))
                / ((mean_a * mean_a + mean_b * mean_b + c1)
                    * (variance_a + variance_b + c2)));
        }
    }
    if scores.is_empty() {
        return Err("no comparable blocks".into());
    }
    Ok(mean(&scores))
}

fn score(left: &Path, right: &Path) -> Result<f64, String> {
    image_ssim(&read_ppm(left)?, &read_ppm(right)?)
}

fn frame_files(directory: &Path) -> Result<Vec<PathBuf>, String> {
    let mut paths = fs::read_dir(directory)
        .map_err(|error| format!("{}: {error}", directory.display()))?
        .filter_map(Result::ok)
        .map(|entry| entry.path())
        .filter(|path| path.file_name().is_some_and(|name| {
            let name = name.to_string_lossy();
            name.starts_with("frame_") && name.ends_with(".ppm")
        }))
        .collect::<Vec<_>>();
    paths.sort();
    Ok(paths)
}

fn score_directories(psx_dir: &Path, pc_dir: &Path) -> Result<(), String> {
    for psx_path in frame_files(psx_dir)? {
        let name = psx_path.file_name().unwrap();
        let pc_path = pc_dir.join(name);
        if !pc_path.is_file() {
            continue;
        }
        let value = score(&psx_path, &pc_path)?;
        println!("{}\t{value:.12}", name.to_string_lossy());
    }
    Ok(())
}

fn score_pairs() -> Result<(), String> {
    let mut request = String::new();
    io::stdin().read_to_string(&mut request).map_err(|error| error.to_string())?;
    for line in request.lines() {
        let (left, right) = line.split_once('\t')
            .ok_or_else(|| format!("{line}: expected two tab-separated paths"))?;
        println!("{:.12}", score(Path::new(left), Path::new(right))?);
    }
    Ok(())
}

fn main() -> Result<(), String> {
    let args = env::args().skip(1).collect::<Vec<_>>();
    match args.as_slice() {
        [flag] if flag == "--pairs" => score_pairs(),
        [psx_dir, pc_dir] => score_directories(Path::new(psx_dir), Path::new(pc_dir)),
        _ => Err("usage: ssim PSX_DIR PC_DIR | ssim --pairs < pairs.tsv".into()),
    }
}
