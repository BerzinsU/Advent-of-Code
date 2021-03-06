(ns puzzle_tests
  (:require [clojure.test :refer :all]
            [advent2020.puzzles :refer :all]))

(deftest valid_passports_1
  (testing "Check first example passports"
    (is (= 2 (count (check-passports "ecl:gry pid:860033327 eyr:2020 hcl:#fffffd\nbyr:1937 iyr:2017 cid:147 hgt:183cm\n\niyr:2013 ecl:amb cid:350 eyr:2023 pid:028048884\nhcl:#cfa07d byr:1929\n\nhcl:#ae17e1 iyr:2013\neyr:2024\necl:brn pid:760753108 byr:1931\nhgt:179cm\n\nhcl:#cfa07d eyr:2025 pid:166559648\niyr:2011 ecl:brn hgt:59in"))))))

(deftest valid_passports_2
  (testing "Check second example passports"
    (is (= 0 (count (validate-passports (parse-passports "eyr:1972 cid:100\nhcl:#18171d ecl:amb hgt:170 pid:186cm iyr:2018 byr:1926\n\niyr:2019\nhcl:#602927 eyr:1967 hgt:170cm\necl:grn pid:012533040 byr:1946\n\nhcl:dab227 iyr:2012\necl:brn hgt:182cm pid:021572410 eyr:2020 byr:1992 cid:277\n\nhgt:59cm ecl:zzz\neyr:2038 hcl:74454a iyr:2023\npid:3556412378 byr:2007")))))
    (is (= 4 (count (validate-passports (parse-passports "pid:087499704 hgt:74in ecl:grn iyr:2012 eyr:2030 byr:1980\nhcl:#623a2f\n\neyr:2029 ecl:blu cid:129 byr:1989\niyr:2014 pid:896056539 hcl:#a97842 hgt:165cm\n\nhcl:#888785\nhgt:164cm byr:2001 iyr:2015 cid:88\npid:545766238 ecl:hzl\neyr:2022\n\niyr:2010 hgt:158cm hcl:#b6652a ecl:blu byr:1944 eyr:2021 pid:093154719")))))))


(deftest decode_seat
  (testing "Decoding seat ID form giberish"
    (is (= 567 (get_seat_id "BFFFBBFRRR")))
    (is (= 119 (get_seat_id "FFFBBBFRRR")))
    (is (= 820 (get_seat_id "BBFFBBFRLL")))))

(deftest count_yeses
  (testing "Counting yeses"
    (is (= 3 (count-group-yes "abc")))
    (is (= 3 (count-group-yes "a\nb\nc")))
    (is (= 3 (count-group-yes "ab\nac")))
    (is (= 1 (count-group-yes "a\na\na\na")))
    (is (= 1 (count-group-yes "b")))
    (is (= 11 (count-all-groups (clojure.string/split "abc\n\na\nb\nc\n\nab\nac\n\na\na\na\na\n\nb" #"\n\n"))))))

(deftest count_unanimous_yeses
  (testing "Counting unanimous yeses"
    (is (= 3 (count-group-unanimous-yes "abc")))
    (is (= 0 (count-group-unanimous-yes "a\nb\nc")))
    (is (= 1 (count-group-unanimous-yes "ab\nac")))
    (is (= 1 (count-group-unanimous-yes "a\na\na\na")))
    (is (= 1 (count-group-unanimous-yes "b")))
    (is (= 6 (count-all-unanimous-groups (clojure.string/split "abc\n\na\nb\nc\n\nab\nac\n\na\na\na\na\n\nb" #"\n\n"))))))

(def bag_input (-> "light red bags contain 1 bright white bag, 2 muted yellow bags.\ndark orange bags contain 3 bright white bags, 4 muted yellow bags.\nbright white bags contain 1 shiny gold bag.\nmuted yellow bags contain 2 shiny gold bags, 9 faded blue bags.\nshiny gold bags contain 1 dark olive bag, 2 vibrant plum bags.\ndark olive bags contain 3 faded blue bags, 4 dotted black bags.\nvibrant plum bags contain 5 faded blue bags, 6 dotted black bags.\nfaded blue bags contain no other bags.\ndotted black bags contain no other bags."
                   (clojure.string/split #"\n")
                   (unpack unpack_matroska)))

(def packer_input_1 (-> "shiny gold bags contain 2 dark red bags.\ndark red bags contain 2 dark orange bags.\ndark orange bags contain 2 dark yellow bags.\ndark yellow bags contain 2 dark green bags.\ndark green bags contain 2 dark blue bags.\ndark blue bags contain 2 dark violet bags.\ndark violet bags contain no other bags."
                        (clojure.string/split #"\n")
                        (unpack unpack_matroska_with_counts)
                        (->>
                          (apply merge))))

(def packer_input_2 (-> "shiny gold bags contain 1 dark olive bag, 2 vibrant plum bags.\ndark olive bags contain 3 faded blue bags, 4 dotted black bags.\nvibrant plum bags contain 5 faded blue bags, 6 dotted black bags.\nfaded blue bags contain no other bags.\ndotted black bags contain no other bags."
                        (clojure.string/split #"\n")
                        (unpack unpack_matroska_with_counts)
                        (->>
                          (apply merge))))

(deftest count_wrapper_bags
  (testing "Counting Bags that can wrap"
    (is (= 4 (count-wrapping-bags bag_input)))
    (is (= 126 (dec (packer packer_input_1 :shiny_gold 1))))
    (is (= 32 (dec (packer packer_input_2 :shiny_gold 1))))))


(deftest walk_the_stack
  (testing "Walking stack of instructions"
    (is (= [5 false] (walk-the-stack [["nop" "+0"] ["acc" "+1"] ["jmp" "+4"] ["acc" "+3"] ["jmp" "-3"] ["acc" "-99"] ["acc" "+1"] ["jmp" "-4"] ["acc" "+6"]])))
    (is (= [8 true] (fix-the-stack [["nop" "+0"] ["acc" "+1"] ["jmp" "+4"] ["acc" "+3"] ["jmp" "-3"] ["acc" "-99"] ["acc" "+1"] ["jmp" "-4"] ["acc" "+6"]])))))

(deftest find_wrong_sum
  (testing "Find the number that doesnt sum from previous"
    (is (= 127 (read-XMAS-weakness 5 [35 20 15 25 47 40 62 55 65 95 102 117 150 182 127 219 299 277 309 576])))
    (is (= 62 (exploit-XMAS-weakness 127 [35 20 15 25 47 40 62 55 65 95 102 117 150 182 127 219 299 277 309 576])))))
