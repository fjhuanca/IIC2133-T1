#!/bin/bash
make
mkdir results
mkdir results/easy
mkdir results/medium
mkdir results/hard
./filters imagenes/easy/test_1.png results/easy/test_1_area_5_60.png area 5 60
./filters imagenes/easy/test_1.png results/easy/test_1_delta_05.png delta 0.5
./filters imagenes/easy/test_2.png results/easy/test_2_area_12_40.png area 12 40
./filters imagenes/easy/test_2.png results/easy/test_2_area_50_5.png area 50 5
./filters imagenes/easy/test_2.png results/easy/test_2_delta_001.png delta 0.001
./filters imagenes/easy/test_3.png results/easy/test_3_area_50_40.png area 50 40
./filters imagenes/easy/test_3.png results/easy/test_3_delta_001.png delta 0.001
./filters imagenes/easy/test_3.png results/easy/test_3_delta_01.png delta 0.01
./filters imagenes/easy/test_4.png results/easy/test_4_area_18_30.png area 18 30
./filters imagenes/easy/test_4.png results/easy/test_4_delta_001.png delta 0.001


./filters imagenes/medium/mona_lisa.png results/medium/monalisa_area_5_30.png area 5 30
./filters imagenes/medium/mona_lisa.png results/medium/monalisa_delta_025.png delta 0.25
./filters imagenes/medium/moon.png results/medium/moon_area_20_50.png area 20 50
./filters imagenes/medium/moon.png results/medium/moon_delta_001.png delta 0.01
./filters imagenes/medium/moon.png results/medium/moon_delta_005.png delta 0.05


./filters imagenes/hard/campus.png results/hard/campus_area_200_0.png area 200 0
./filters imagenes/hard/campus.png results/hard/campus_delta_001.png delta 0.01
./filters imagenes/hard/campus.png results/hard/campus_delta_003.png delta 0.03
./filters imagenes/hard/campus.png results/hard/campus_delta_005.png delta 0.05

./filters imagenes/hard/moon.png results/hard/moon_area_500_7.png area 500 7
./filters imagenes/hard/moon.png results/hard/moon_delta_0008.png delta 0.008

./filters imagenes/hard/plate.png results/hard/plate_area_100_60.png area 100 60
./filters imagenes/hard/plate.png results/hard/plate_delta_0005.png delta 0.005


# declare -a difficulty=("easy" "medium" "hard")
# for j in ${difficulty[@]}
# do
#     echo "Running $j Tests:"
#     for i in {1..6..1}
#     do
#         echo "$j $i:"
#         time ./kevin-21 tests/${j}/test_${i}.txt results/${j}/test_${i}_out.txt
#     done
#     echo "Finished $j Tests"
# done