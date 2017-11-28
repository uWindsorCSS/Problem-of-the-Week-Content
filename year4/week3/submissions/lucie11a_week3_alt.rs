use std::collections::{ HashMap };
use std::io::{ self, Read, Write };
use std::hash::{ BuildHasherDefault, Hasher };

pub type FNVMap<K, V> = HashMap<K, V, BuildHasherDefault<FNVHash>>;

pub struct FNVHash(u64);

impl Hasher for FNVHash {
    #[inline]
    fn write(&mut self, bytes: &[u8]) {
        for b in bytes {
            self.0 = self.0.wrapping_mul(0x100000001b3);
            self.0 ^= *b as u64
        }
    }

    #[inline]
    fn finish(&self) -> u64 {
        self.0
    }
}

impl Default for FNVHash {
    #[inline]
    fn default() -> Self {
        FNVHash(0xcbf29ce484222325)
    }
}


struct BitSet {
    data: Vec<u64>,
}

impl BitSet {
    fn new() -> Self {
        Self {
            data: vec![0; 1024],
        }
    }

    fn set(&mut self, idx: usize) {
        let off = idx >> 6;
        let len = self.data.len();
        if off <= len {
            self.data.resize(len * 2, 0);
        }
    
        self.data[idx >> 6] |= 1 << (idx & 63);
    }
    
    fn get(&self, idx: usize) -> bool {
        (self.data[idx >> 6] & (1 << (idx & 63))) != 0
    }
}

fn main() {
    let mut input = String::with_capacity(1024);
    io::stdin().read_to_string(&mut input).unwrap();
    
    let mut find_line = input.lines().rev().next().map(str::split_whitespace).unwrap();
    let u = find_line.next().unwrap();
    let t = find_line.next().map(str::parse::<i32>).unwrap().unwrap();

    let mut lines = input.lines();

    let n = lines.next().map(str::parse).unwrap().unwrap();

    let mut friends = BitSet::new();
    for mut l in lines.by_ref().take(n).map(str::split_whitespace) {
        let a = l.next().unwrap();
        let b = l.next().unwrap();
        if a == u {
            friends.set(b.parse().unwrap());
        } else if b == u {
            friends.set(a.parse().unwrap());
        }
    }

    let m = lines.next().map(str::parse).unwrap().unwrap();

    let mut posts = FNVMap::with_capacity_and_hasher(1024, Default::default());
    for mut l in lines.by_ref().take(m).map(str::split_whitespace) {
        let x = l.next().map(str::parse).unwrap().unwrap();
        if friends.get(x) {
            let y = l.next().unwrap();
            let z = l.next().map(str::parse::<i32>).unwrap().unwrap();
            *posts.entry(y).or_insert(0) += z;
        }
    }

    let stdout = io::stdout();
    let mut h = stdout.lock();
    for (post, _) in posts.iter().filter(|&(_, n)| *n >= t) {
        writeln!(&mut h, "{}", post).unwrap();
    }
}