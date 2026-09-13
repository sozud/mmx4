use crate::types::Function;
use std::collections::HashMap;

pub struct LevenshteinHashMap {
    pub map: HashMap<Vec<u8>, Vec<Function>>,
    threshold: f64,
}

pub(crate) fn levenshtein_similarity(s1: &[u8], s2: &[u8], threshold: f64) -> f64 {
    if s1 == s2 {
        return 1.0;
    }
    let len1 = s1.len();
    let len2 = s2.len();
    if len1 == 0 || len2 == 0 {
        return if len1 == len2 { 1.0 } else { 0.0 };
    }
    let long = len1.max(len2) as f64;
    let short = len1.min(len2) as f64;
    if short + 1e-9 < threshold * long {
        // length diff exceeds edits threshold
        return 0.0;
    }
    // 2-row DP: O(m) memory
    let mut prev: Vec<u32> = (0..=len2 as u32).collect();
    let mut curr: Vec<u32> = vec![0; len2 + 1];

    for i in 1..=len1 {
        curr[0] = i as u32;
        let a = s1[i - 1];
        for j in 1..=len2 {
            curr[j] = if a == s2[j - 1] {
                prev[j - 1]
            } else {
                prev[j - 1].min(prev[j]).min(curr[j - 1]) + 1
            };
        }
        std::mem::swap(&mut prev, &mut curr);
    }

    (long - prev[len2] as f64) / long
}

impl LevenshteinHashMap {
    pub fn new(threshold: f64) -> Self {
        Self {
            map: HashMap::new(),
            threshold,
        }
    }
    pub fn len(&self) -> usize {
        self.map.len()
    }
    pub fn iter(&self) -> impl Iterator<Item = (&Vec<u8>, &Vec<Function>)> {
        self.map.iter()
    }

    pub fn get(&mut self, key: &[u8]) -> Option<&mut Vec<Function>> {
        if self.map.contains_key(key) {
            return self.map.get_mut(key);
        }
        let mut closest_key: Option<Vec<u8>> = None;
        let mut best_sim = -1.0;
        let threshold = self.threshold;

        for k in self.map.keys() {
            let sim = levenshtein_similarity(key, k, threshold);
            if sim >= self.threshold && sim > best_sim {
                best_sim = sim;
                closest_key = Some(k.clone());
            }
        }

        if let Some(k) = &closest_key {
            self.map.get_mut(k)
        } else {
            None
        }
    }

    pub fn insert(&mut self, mut value: Function) {
        if let Some(cluster) = self.map.get_mut(&value.key) {
            value.similarity = 1.0;
            cluster.push(value);
            return;
        }

        let mut closest_key: Option<Vec<u8>> = None;
        let mut best_sim = -1.0;
        let threshold = self.threshold;

        for k in self.map.keys() {
            let sim = levenshtein_similarity(&value.key, k, threshold);
            if sim >= self.threshold && sim > best_sim {
                best_sim = sim;
                closest_key = Some(k.clone());
            }
        }

        if let Some(k) = &closest_key {
            value.similarity = best_sim;
            self.map.get_mut(k).expect("key from keys()").push(value);
        } else {
            value.similarity = 1.0;
            self.map.insert(value.key.clone(), vec![value]);
        }
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_insert_and_get_same_cluster() {
        let mut map = LevenshteinHashMap::new(0.95);
        let func1 = Function {
            name: String::from("func1"),
            ops: vec![],
            key: vec![1, 2, 3],
            decompiled: false,
            dir: String::from("testdir1"),
            file: String::from("testfile1"),
            similarity: 0.0,
        };
        let func2 = Function {
            name: String::from("func2"),
            ops: vec![],
            key: vec![1, 2, 3],
            decompiled: false,
            dir: String::from("testdir2"),
            file: String::from("testfile2"),
            similarity: 0.0,
        };

        map.insert(func1.clone());
        map.insert(func2.clone());

        // both functions should be in the same cluster
        let result1 = map.get(&vec![1, 2, 3]);
        assert_eq!(result1.expect("has items").len(), 2);
    }

    #[test]
    fn test_insert_and_get_different_cluster() {
        let mut map = LevenshteinHashMap::new(0.95);
        let func1 = Function {
            name: String::from("func1"),
            ops: vec![],
            key: vec![1, 2, 3],
            decompiled: false,
            dir: String::from("testdir1"),
            file: String::from("testfile1"),
            similarity: 0.0,
        };
        let func2 = Function {
            name: String::from("func2"),
            ops: vec![],
            key: vec![4, 5, 6],
            decompiled: false,
            dir: String::from("testdir2"),
            file: String::from("testfile2"),
            similarity: 0.0,
        };

        map.insert(func1.clone());
        map.insert(func2.clone());

        // functions should be in different clusters
        let result1 = map.get(&vec![1, 2, 3]);
        assert_eq!(result1.expect("has items").len(), 1);

        let result2 = map.get(&vec![4, 5, 6]);
        assert_eq!(result2.expect("has items").len(), 1);
    }

    #[test]
    fn test_insert_picks_most_similar_cluster() {
        let mut map = LevenshteinHashMap::new(0.5);
        let base_a = Function {
            name: String::from("a"),
            ops: vec![],
            key: vec![1, 2, 3, 4, 5, 6, 7, 8],
            decompiled: false,
            dir: String::from("d"),
            file: String::from("f"),
            similarity: 0.0,
        };
        let base_b = Function {
            name: String::from("b"),
            ops: vec![],
            key: vec![9, 9, 9, 9, 9, 9, 9, 9],
            decompiled: false,
            dir: String::from("d"),
            file: String::from("f"),
            similarity: 0.0,
        };
        map.insert(base_a);
        map.insert(base_b);

        let probe = Function {
            name: String::from("probe"),
            ops: vec![],
            key: vec![1, 2, 3, 9, 9, 9, 9, 9],
            decompiled: false,
            dir: String::from("d"),
            file: String::from("f"),
            similarity: 0.0,
        };
        map.insert(probe);

        assert_eq!(map.len(), 2);
        let b_cluster = map.get(&vec![9, 9, 9, 9, 9, 9, 9, 9]).unwrap();
        assert_eq!(b_cluster.len(), 2);
        assert!(b_cluster.iter().any(|f| f.name == "probe"));
    }

    #[test]
    fn test_similarity_length_prefilter() {
        assert_eq!(
            levenshtein_similarity(&[1, 2], &[1, 2, 3, 4, 5, 6, 7, 8, 9, 10], 0.94),
            0.0
        );
        assert_eq!(levenshtein_similarity(&[1, 2, 3], &[1, 2, 3], 0.94), 1.0);
    }
}
