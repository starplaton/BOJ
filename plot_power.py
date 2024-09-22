import matplotlib.pyplot as plt
from datetime import datetime
import matplotlib.font_manager as fm
import os


def plot_power_history(log_file="history.log", output_file="power_history.png"):
    """
    로그 파일을 읽어 시간에 따른 전투력 변화를 그래프로 그립니다.

    :param log_file: 로그 파일 이름
    :param output_file: 저장할 그래프 이미지 파일 이름
    """
    timestamps = []
    powers = []

    with open(log_file, "r", encoding="utf-8") as f:
        for line in f:
            if line.strip().startswith("Timestamp:"):
                timestamp_str = line.strip().split("Timestamp: ")[1]
                try:
                    timestamp = datetime.strptime(timestamp_str, "%Y-%m-%d %H:%M:%S")
                    timestamps.append(timestamp)
                except ValueError:
                    print(f"잘못된 타임스탬프 형식: {timestamp_str}")
            elif line.strip().startswith("Power:"):
                try:
                    power = float(line.strip().split("Power: ")[1])
                    powers.append(power)
                except ValueError:
                    print(f"잘못된 전투력 형식: {line.strip()}")

    if not timestamps or not powers:
        print("로그 파일에 충분한 데이터가 없습니다.")
        return

    # matplotlib에 한글 폰트 설정
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

    plt.figure(figsize=(10, 5))
    plt.plot(timestamps, powers, marker="o", linestyle="-")
    plt.xlabel("시간")
    plt.ylabel("전투력 (Power)")
    plt.title("시간에 따른 전투력 변화")
    plt.grid(True)
    plt.tight_layout()
    plt.savefig(output_file)
    plt.show()
    plt.close()
    print(f"그래프가 '{output_file}' 파일로 저장되었습니다.")


# 사용 예제
plot_power_history()
