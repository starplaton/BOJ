#!/bin/bash

echo "Test Start ---------------"

# 테스트 함수 정의
run_test() {
    local input_file=$1
    local output_file=$2
    local filename=$3

    # 프로그램 실행 시간 측정 시작
    start_time=$(date +%s%3N)

    # 프로그램 실행 및 출력 저장
    cp solution/main.js solution/main.cjs
    node solution/main.cjs readizDebug < "$input_file" > "/tmp/temp_${filename}.txt"

    # 프로그램 실행 시간 측정 종료
    end_time=$(date +%s%3N)

    # 소요 시간 계산 (ms 단위)
    duration=$((end_time - start_time))

    # diff 명령어로 결과 비교
    diff_result=$(diff -w "/tmp/temp_${filename}.txt" "$output_file")
    if [ $? -eq 0 ]; then
        echo "Test ${filename} Passed (${duration} ms)"
    else
        echo "----------------"
        echo "Test ${filename} INPUT"
        cat $input_file
        echo ""
        echo "----------------"
        echo "Test ${filename} ANS"
        cat $output_file
        echo ""
        echo "----------------"
        echo "Test ${filename} YOURS"
        cat "/tmp/temp_${filename}.txt"
        echo ""
        echo "Test ${filename} Failed (${duration} ms)"
    fi

    # 임시 파일 삭제
    #rm "/tmp/temp_${filename}.txt"
}

# 인자를 받았는지 확인
if [ $# -eq 1 ]; then
    # 주어진 인자를 파일 이름으로 사용
    filename="$1"
    input_file="input/${filename}.txt"
    output_file="output/${filename}.txt"

    # 단일 테스트 실행
    run_test "$input_file" "$output_file" "$filename"
else
    # 인자가 없으면 모든 파일에 대해 루프 실행
    for input_file in input/*.txt; do
        # 파일 이름 추출 (경로 및 확장자 제외)
        filename=$(basename -- "$input_file")
        filename="${filename%.*}"

        # 해당하는 output 파일 경로
        output_file="output/${filename}.txt"

        # 테스트 실행
        run_test "$input_file" "$output_file" "$filename"
    done
fi