// Squirrel Frenzy

import Foundation

func uniquePairs(chestnuts: [Int], c: Int, s: Int) {

    var found = 0
    var seen = [Int: Int]()

    for hole in chestnuts {
        if let dif = seen[s-hole] {
            found += dif
        }

        if var _ = seen[hole] {
            seen[hole]! += 1
        } else { 
            seen[hole] = 1 
        }
    }

    print((found >= c ? "True" : "False"))
}


let _ = readLine()
var chestnuts = [Int]()

if let h = readLine() {

    let strs = h.components(separatedBy: " ")
    for str in strs {
        
        if let converted = Int(str) { chestnuts.append(converted) }
        else { print("Couldn't convert hole to an int") }
    }
} else { print("Error reading holes") }



if let line = readLine() {

    let strs = line.components(separatedBy: " ")
    if let c = Int(strs[0]), let s = Int(strs[1]) {
        uniquePairs(chestnuts: chestnuts, c: c, s: s)
    
    } else { print("Couldnt convert c and s to int") }
} else { print("Couldnt read c and s from input") }

