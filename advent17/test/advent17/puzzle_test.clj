(ns advent17.puzzle-test
  (:require [clojure.test :refer :all]
            [advent17.puzzles :refer :all]))

(deftest inverse-captcha-tests
  (testing "Inverse Captcha - tests from description"
    (is (= (inverse-captcha 1122) 3))
    (is (= (inverse-captcha 1111) 4))
    (is (= (inverse-captcha 1234) 0))
    (is (= (inverse-captcha 91212129) 9))))

(deftest halfway-captcha-tests
  (testing "Inverse Captcha - tests from part two description"
    (is (= (halfway-captcha 1212) 6))
    (is (= (halfway-captcha 1221) 0))
    (is (= (halfway-captcha 123123) 12))
    (is (= (halfway-captcha 12131415) 4))))

(deftest spreadsheet-checksum-tests
  (testing "Corrupted checksum - test spreadsheet sum"
    (is (= (corruption-checksum [[5 1 9 5]
                                 [7 5 3]
                                 [2 4 6 8 8]])
           18))))

;(deftest spreadsheet-divider-checksum-tests
;  (testing "Corrupted checksum - test spreadsheet sum for clean divisions"
;    (is (= (corruption-checksum-for-dividers [[5 9 2 8]
;                                              [9 4 7 3]
;                                              [3 8 6 5]])
;           9))))

(deftest validate-passphrase-list-tests
  (testing "High-Entropy Passphrases - test if words are unique"
    (is (= (validate-passphrase-list ["aa bb cc dd ee"
                                      "aa bb cc dd aa"
                                      "aa bb cc dd aaa"])
           2))))

(deftest validate-passphrase-list-on-anagrams-tests
  (testing "High-Entropy Passphrases - test if words are unique"
    (is (= (validate-passphrase-list-on-anagrams ["abcde fghij"
                                                  "abcde xyz ecdab"
                                                  "a ab abc abd abf abj"
                                                  "iiii oiii ooii oooi oooo"
                                                  "oiii ioii iioi iiio"])
           3))))

(deftest jump-out-of-list-test
  (testing "A Maze of Twisty Trampolines - test step counter"
    (is (= (jump-out-of-list [0 3 0 1 -3])
           5))))

(deftest jump-out-of-list-test
  (testing "A Maze of Twisty Trampolines - test step counter"
    (is (= (jump-out-of-list-with-decrease [0 3 0 1 -3])
           10))))

(deftest count-reallocate-memory-steps-tests
  (testing "Memory Reallocation - count rellocaton steps necessary "
    (is (= (count-reallocate-memory-steps [0 2 7 0])
           5))))

(deftest count-reallocate-memory-loop-tests
  (testing "Memory Reallocation - count rellocaton steps necessary "
    (is (= (count-reallocate-memory-loop [0 2 7 0])
           4))))