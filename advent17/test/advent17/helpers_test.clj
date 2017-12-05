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