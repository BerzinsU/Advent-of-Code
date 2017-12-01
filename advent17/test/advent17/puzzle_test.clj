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
