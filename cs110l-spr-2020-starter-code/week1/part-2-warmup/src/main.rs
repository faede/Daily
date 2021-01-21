/* The following exercises were borrowed from Will Crichton's CS 242 Rust lab. */

use std::collections::HashSet;

fn main() {
    println!("Hi! Try running \"cargo test\" to run tests.");
}

fn add_n(v: Vec<i32>, n: i32) -> Vec<i32> {
    let mut t = Vec::new();
    for i in v.iter(){
        t.push(*i + n);
    }
    t
}

fn add_n_inplace(v: &mut Vec<i32>, n: i32) {
    for i in v.iter_mut(){
        *i += n;
    }
}

fn dedup(v: &mut Vec<i32>) {
    let mut t = Vec::new();
    let mut set: HashSet<i32> = HashSet::new();
    for i in v.iter(){
        if !set.contains(i) {
            t.push(*i);
            set.insert(*i);
        }
    }
    //println!("test  t : {:?}", t);
    *v = t.clone();
    //println!("test  v : {:?}", v);
}

#[cfg(test)]
mod test {
    use super::*;

    #[test]
    fn test_add_n() {
        assert_eq!(add_n(vec![1], 2), vec![3]);
    }

    #[test]
    fn test_add_n_inplace() {
        let mut v = vec![1];
        add_n_inplace(&mut v, 2);
        assert_eq!(v, vec![3]);
    }

    #[test]
    fn test_dedup() {
        let mut v = vec![3, 1, 0, 1, 4, 4];
        dedup(&mut v);
        assert_eq!(v, vec![3, 1, 0, 4]);
    }
}
