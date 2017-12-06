(ns advent17.helpers-test
  (:require [clojure.test :refer :all]
            [advent17.helpers :refer :all]))

;
;(deftest row-checksum-tests
;  (testing "Corrupted checksum - test if clean division is found"
;    (is (= (calculate-row-division-checksum [5 9 2 8]) 4))
;    (is (= (calculate-row-division-checksum [9 4 7 3]) 3))
;    (is (= (calculate-row-division-checksum [3 8 6 5]) 2))))

(deftest calc-centered-octagonal-number-tests
  (testing "Spiral Memory - test that centered-octagonal-number calculate correctly"
    (is (= (calc-centered-octagonal-number 1) 1))
    (is (= (calc-centered-octagonal-number 2) 9))
    (is (= (calc-centered-octagonal-number 6) 121))))

(deftest centered-octagonal-number-seq-tests
  (testing "Spiral Memory - test that centered-octagonal-number-seq returns correct list"
    (is (= (take 5 (centered-octagonal-number-seq))
           '(1 9 25 49 81)))))

;(deftest generate-outward-spirral-tests
;  (testing "Spiral Memory - generate outwards spiral array "
;    (is (= (generate-outward-spiral 25)
;           [[17 16 15 14 13]
;            [18 5 4 3 12]
;            [19 6 1 2 11]
;            [20 7 8 9 10]
;            [21 22 23]]))))

(deftest validate-passphrase-tests
  (testing "High-Entropy Passphrases - test if words are unique"
    (is (= (validate-passphrase "aa bb cc dd ee")
           true))
    (is (= (validate-passphrase "aa bb cc dd aa")
           false))
    (is (= (validate-passphrase "aa bb cc dd aaa")
           true))))

(deftest validate-passphrase-anagram-tests
  (testing "High-Entropy Passphrases - test if words are unique"
    (is (= (validate-passphrase-anagram "abcde fghij")
           true))
    (is (= (validate-passphrase-anagram "abcde xyz ecdab")
           false))
    (is (= (validate-passphrase-anagram "a ab abc abd abf abj")
           true))
    (is (= (validate-passphrase-anagram "iiii oiii ooii oooi oooo")
           true))
    (is (= (validate-passphrase-anagram "oiii ioii iioi iiio")
           false))))

(deftest check-history-tests
  (testing "test if memory is reallocated correctly"
    (is (= (already-in-history? [[0 1] [1 1]] [0 1])
           true))
    (is (= (already-in-history? [[0 1] [1 1]] [2 2])
           false))))

(deftest reallocate-memory-tests
  (testing "test if memory is reallocated correctly"
    (is (= (reallocate-memory [0 2 7 0])
           [2 4 1 2]))
    (is (= (reallocate-memory [2 4 1 2])
           [3 1 2 3]))
    (is (= (reallocate-memory [3 1 2 3])
           [0 2 3 4]))
    (is (= (reallocate-memory [0 2 3 4])
           [1 3 4 1]))
    (is (= (reallocate-memory [1 3 4 1])
           [2 4 1 2]))))