import subprocess
from collections import defaultdict
import matplotlib.pyplot as plt
import os
import matplotlib.font_manager as fm

# Git 로그 명령어 실행
git_log_cmd = ["git", "log", "--pretty=format:%ad", "--date=short", "--numstat"]
result = subprocess.run(git_log_cmd, stdout=subprocess.PIPE, text=True)

# 데이터 파싱
lines = result.stdout.split("\n")
data = defaultdict(int)
current_date = None

for line in lines:
    if not line.strip():
        continue
    if len(line) == 10 and line[4] == "-" and line[7] == "-":
        # 날짜 라인
        current_date = line.strip()
    else:
        # numstat 라인: 추가된 줄 수, 삭제된 줄 수, 파일명
        parts = line.split("\t")
        if len(parts) >= 2 and current_date:
            added = parts[0]
            try:
                added = int(added)
                data[current_date] += added
            except ValueError:
                # 바이너리 파일 등 숫자가 아닌 경우 무시
                pass

# 데이터 정렬
sorted_dates = sorted(data.keys())
sorted_added = [data[date] for date in sorted_dates]

try:
    font_path = "/usr/share/fonts/truetype/nanum/NanumGothic.ttf"  # Linux 예시
    if not os.path.exists(font_path):
        # macOS 예시
        font_path = "/Library/Fonts/NanumGothic.ttf"
        if not os.path.exists(font_path):
            # Windows 예시
            font_path = "C:\\Windows\\Fonts\\NanumGothic.ttf"
    font_prop = fm.FontProperties(fname=font_path)
    plt.rcParams["font.family"] = font_prop.get_name()
    plt.rcParams["axes.unicode_minus"] = False  # 음수 표시 설정
except Exception as e:
    print(f"폰트 설정 오류: {e}")
    print("한글 폰트가 제대로 설정되지 않을 수 있습니다.")

# 시각화
font_prop = fm.FontProperties(fname=font_path)
plt.rcParams["font.family"] = font_prop.get_name()
plt.rcParams["axes.unicode_minus"] = False  # 음수 표시 설정
plt.figure(figsize=(12, 6))
plt.plot(sorted_dates, sorted_added, marker="o")
plt.xlabel("날짜")
plt.ylabel("추가된 코드 줄 수")
plt.title("날짜별 Git 커밋 코드 줄 수")
plt.xticks(rotation=45)
plt.tight_layout()
plt.savefig("git_line.png")
plt.show()
