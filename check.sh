#!/bin/bash

# 오늘 날짜 (YYYY-MM-DD 형식)
today=$(date +"%Y-%m-%d")

# 오늘의 커밋 로그를 확인하여 수정된 파일의 라인 수를 추출
total_lines=$(git log --since="$today 00:00" --until="$today 23:59" --pretty=tformat: --numstat | awk '{added += $1; removed += $2} END {print added + removed}')

# 출력
if [ -z "$total_lines" ]; then
    echo "오늘 제출한 코드가 없습니다."
else
    echo "오늘 제출한 총 코드 줄 수: $total_lines"
fi
