from datetime import datetime
from bs4 import BeautifulSoup
from selenium import webdriver
from selenium.webdriver.chrome.options import Options
import matplotlib.pyplot as plt
import requests
import re
import sys
import math
import time
import hashlib
import random
import string
import matplotlib.font_manager as fm
import os

# ============================
# CodeforcesAPI 클래스 정의
# ============================


class CodeforcesAPI:
    BASE_URL = "https://codeforces.com/api/"

    def __init__(self, api_key=None, api_secret=None):
        self.api_key = api_key
        self.api_secret = api_secret
        self.last_request_time = 0

    def _generate_api_sig(self, method, params):
        # Generate a random 6-character string
        rand = "".join(random.choices(string.digits + string.ascii_letters, k=6))

        # Sort parameters lexicographically by key, then by value
        sorted_params = sorted(params.items())
        param_str = "&".join(f"{k}={v}" for k, v in sorted_params)

        # Construct the string to hash
        to_hash = f"{rand}/{method}?{param_str}#{self.api_secret}"

        # Compute SHA-512 hash
        hash_obj = hashlib.sha512(to_hash.encode("utf-8"))
        hash_hex = hash_obj.hexdigest()

        # Combine rand and hash
        api_sig = rand + hash_hex
        return api_sig

    def _make_request(self, method, params=None, auth=False):
        if params is None:
            params = {}

        if auth:
            if not self.api_key or not self.api_secret:
                raise ValueError(
                    "API key and secret must be provided for authenticated requests."
                )
            current_time = int(time.time())
            params["apiKey"] = self.api_key
            params["time"] = current_time
            api_sig = self._generate_api_sig(method, params)
            params["apiSig"] = api_sig

        # Rate limiting: 1 request per 2 seconds
        elapsed = time.time() - self.last_request_time
        if elapsed < 2:
            time.sleep(2 - elapsed)

        url = self.BASE_URL + method
        response = requests.get(url, params=params)
        data = response.json()
        self.last_request_time = time.time()

        if data["status"] == "OK":
            return data["result"]
        else:
            raise Exception(f"API Error: {data.get('comment', 'No comment provided')}")

    def get_user_status(self, handle, from_=1, count=1000, auth=False):
        method = "user.status"
        params = {"handle": handle, "from": from_, "count": count}
        return self._make_request(method, params, auth)


# ============================
# 스크래핑 관련 함수 정의
# ============================


def setup_selenium():
    """
    Selenium WebDriver를 헤드리스 모드로 설정하고 반환합니다.
    """
    chrome_options = Options()
    chrome_options.add_argument("--headless")  # 헤드리스 모드
    chrome_options.add_argument("--no-sandbox")  # 샌드박스 비활성화 (Linux 환경)
    chrome_options.add_argument("--disable-dev-shm-usage")  # /dev/shm 사용 안 함
    chrome_options.add_argument(
        "--disable-gpu"
    )  # GPU 비활성화 (특히 Linux 환경에서 필요)
    driver = webdriver.Chrome(options=chrome_options)
    return driver


def scrape_solved_ac_profile(driver, url, css_class="css-1midmz7"):
    """
    Selenium을 사용하여 solved.ac 프로필에서 특정 CSS 클래스의 <div> 요소를 스크래핑하고,
    <b> 태그 내의 숫자를 추출하여 리스트로 반환합니다.

    :param driver: Selenium WebDriver 객체
    :param url: 스크래핑할 프로필 URL
    :param css_class: 타겟 <div> 요소의 CSS 클래스
    :return: 추출된 숫자의 리스트
    """
    driver.get(url)
    time.sleep(1)  # 페이지 로드 대기 (필요에 따라 조절)
    page_source = driver.page_source
    soup = BeautifulSoup(page_source, "html.parser")

    div_elements = soup.find_all("div", class_=css_class)

    found_list = []
    for i, div_element in enumerate(div_elements):
        bold_tag = div_element.find("b")
        if bold_tag:
            bold_text = bold_tag.text.strip()
            number = re.search(r"\d+", bold_text)
            if number:
                extracted_number = number.group()
                found_list.append(extracted_number)
            else:
                print(f"div_element[{i}] - 숫자를 찾을 수 없습니다.")
        else:
            print(f"div_element[{i}] - 해당 div에 <b> 태그가 없습니다.")

    return found_list


# ============================
# 전투력 계산 함수 정의
# ============================


def calculate_power(streak, total_problems):
    """
    전투력(power)을 계산하는 함수입니다.

    :param streak: 연속으로 푼 문제 수
    :param total_problems: 총 풀은 문제 수
    :return: 계산된 전투력, 계산 과정 설명
    """
    streak_weight = 100  # 연속 문제 풀이의 가중치
    total_weight = 0.8  # 총 문제 수의 가중치
    streak_multiplier = 0.05  # 연속 문제 풀이의 비율

    # 기본 전투력 계산
    base_power = (streak * streak_weight) + (total_problems * total_weight)

    # 전투력에 추가적인 비율 적용
    power = base_power * (1 + (streak * streak_multiplier))

    swexpert_point = 10709
    power += swexpert_point / 30
    power = power * ((1.01) ** (streak - 5))

    # 랜덤 배율 적용 (±5%)
    random_multiplier = random.uniform(0.775, 1.025)
    power *= random_multiplier

    # 랜덤 보너스 추가 (50~150)
    random_bonus = random.randint(-50, 10)
    power += random_bonus

    # 계산 과정 설명
    calculation_steps = (
        f"Base Power Calculation:\n"
        f"  streak * streak_weight = {streak} * {streak_weight} = {streak * streak_weight}\n"
        f"  total_problems * total_weight = {total_problems} * {total_weight} = {total_problems * total_weight}\n"
        f"  base_power = {streak * streak_weight} + {total_problems * total_weight} = {base_power}\n\n"
        f"Power Calculation with Multiplier:\n"
        f"  streak * streak_multiplier = {streak} * {streak_multiplier} = {streak * streak_multiplier}\n"
        f"  1 + (streak * streak_multiplier) = 1 + {streak * streak_multiplier} = {1 + streak * streak_multiplier}\n"
        f"  power = {base_power} * {1 + streak * streak_multiplier} = {power / random_multiplier - random_bonus} / {random_multiplier}\n\n"
        f"Random Multiplier Applied:\n"
        f"  random_multiplier = {random_multiplier}\n"
        f"  power after multiplier = {power / random_multiplier} * {random_multiplier} = {power - random_bonus}\n\n"
        f"Random Bonus Applied:\n"
        f"  random_bonus = {random_bonus}\n"
        f"  final power = {power - random_bonus} + {random_bonus} = {power}\n"
    )

    return power, calculation_steps


# ============================
# 로그 기록 함수 정의
# ============================


def log_history(
    timestamp, found_list, power, calculation_steps, log_file="history.log"
):
    """
    로그 파일에 현재 시간, 찾은 리스트, 전투력, 계산 과정을 기록합니다.

    :param timestamp: 현재 시간 (datetime 객체)
    :param found_list: 스크래핑을 통해 찾은 숫자 리스트
    :param power: 계산된 전투력
    :param calculation_steps: 전투력 계산 과정 설명
    :param log_file: 로그를 기록할 파일 이름
    """
    with open(log_file, "a", encoding="utf-8") as f:
        formatted_time = timestamp.strftime("%Y-%m-%d %H:%M:%S")
        f.write(f"Timestamp: {formatted_time}\n")
        f.write(f"Found List: {found_list}\n")
        f.write(f"Calculation Formula:\n{calculation_steps}")
        f.write(f"Power: {power:.2f}\n")
        f.write("-" * 50 + "\n")


# ============================
# Codeforces API를 사용한 total_problems 및 streak 계산 함수
# ============================


def calculate_total_problems_api(cf_api, handle):
    """
    Codeforces API를 사용하여 사용자가 해결한 고유 문제의 수를 계산합니다.

    :param cf_api: CodeforcesAPI 객체
    :param handle: Codeforces 핸들
    :return: 해결한 고유 문제 수
    """
    solved_problems = set()
    from_submission = 1
    count = 1000  # 한 번에 가져올 제출 수

    while True:
        try:
            submissions = cf_api.get_user_status(
                handle, from_=from_submission, count=count, auth=False
            )
            if not submissions:
                break

            for submission in submissions:
                if submission.get("verdict") == "OK":
                    problem = submission.get("problem", {})
                    contest_id = problem.get("contestId")
                    index = problem.get("index")
                    if contest_id and index:
                        problem_id = (contest_id, index)
                        solved_problems.add(problem_id)

            if len(submissions) < count:
                break  # 마지막 페이지
            from_submission += count
        except Exception as e:
            print(f"API 오류 발생: {e}")
            break

    total_problems = len(solved_problems)
    return total_problems


def calculate_streak_api(cf_api, handle):
    """
    Codeforces API를 사용하여 사용자의 최근 연속적으로 풀은 문제 수(streak)를 계산합니다.

    :param cf_api: CodeforcesAPI 객체
    :param handle: Codeforces 핸들
    :return: 연속적으로 푼 문제 수
    """
    streak = 0
    from_submission = 1
    count = 1000

    all_submissions = []

    while True:
        try:
            submissions = cf_api.get_user_status(
                handle, from_=from_submission, count=count, auth=False
            )
            if not submissions:
                break
            all_submissions.extend(submissions)
            if len(submissions) < count:
                break
            from_submission += count
        except Exception as e:
            print(f"API 오류 발생: {e}")
            break

    # 가장 최근 제출부터 역순으로 처리
    for submission in reversed(all_submissions):
        if submission.get("verdict") == "OK":
            streak += 1
        else:
            break  # 연속이 끊겼으므로 종료

    return streak


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


# ============================
# 메인 함수 정의
# ============================


def main():
    # ========================
    # 스크래핑을 통한 데이터 추출
    # ========================
    solved_ac_url = (
        "https://solved.ac/profile/franj"  # 자신의 solved.ac 프로필 URL로 변경하세요
    )
    driver = setup_selenium()
    try:
        found_list = scrape_solved_ac_profile(driver, solved_ac_url)
    finally:
        driver.quit()  # 반드시 드라이버를 종료하여 리소스를 해제

    # ========================
    # found_list의 내용 확인
    # ========================
    # 예시 found_list: ['2040', '3', '812']
    # 가정:
    # found_list[0] = 2040 (예: 레벨 또는 다른 지표)
    # found_list[1] = 3 (streak)
    # found_list[2] = 812 (total_problems)

    if len(found_list) < 3:
        print("필요한 데이터가 충분하지 않습니다.")
        return

    try:
        scraped_streak = int(found_list[1])
        scraped_total_problems = int(found_list[2])
    except ValueError:
        print("found_list의 데이터 형식이 올바르지 않습니다.")
        return

    # ========================
    # Codeforces API를 통한 추가 데이터 추출
    # ========================
    # Codeforces 핸들과 API 키/시크릿을 설정하세요
    cf_handle = "FranJ"  # 자신의 Codeforces 핸들로 변경하세요
    api_key = None  # API 키 (필요 시 입력)
    api_secret = None  # API 시크릿 (필요 시 입력)

    # Codeforces API 객체 생성
    cf_api = CodeforcesAPI(api_key=api_key, api_secret=api_secret)

    # API를 통해 얻은 데이터 계산
    api_total_problems = calculate_total_problems_api(cf_api, cf_handle)
    api_streak = calculate_streak_api(cf_api, cf_handle)

    # ========================
    # 스크래핑 데이터와 API 데이터를 합산
    # ========================
    total_problems = scraped_total_problems + api_total_problems
    streak = scraped_streak + api_streak

    # ========================
    # 전투력 계산
    # ========================
    power, calculation_steps = calculate_power(streak, total_problems)

    # ========================
    # 현재 시간 가져오기
    # ========================
    now = datetime.now()

    # ========================
    # 로그 기록
    # ========================
    # found_list에는 스크래핑한 데이터가 포함됩니다.
    # API 데이터를 합산한 후의 total_problems와 streak을 사용합니다.
    # calculation_steps에는 전투력 계산 과정이 포함됩니다.
    # 로그 형식을 더 풍부하고 직관적으로 만들기 위해, 스크래핑과 API 데이터를 명확히 구분합니다.
    log_found_list = {
        "Scraped Data": {
            "streak": scraped_streak,
            "total_problems": scraped_total_problems,
        },
        "API Data": {"streak": api_streak, "total_problems": api_total_problems},
        "Combined Data": {"streak": streak, "total_problems": total_problems},
    }
    log_history(now, log_found_list, power, calculation_steps)

    # ========================
    # 콘솔 출력
    # ========================
    print(f"총 풀은 문제 수 (스크래핑 + API): {total_problems}")
    print(f"연속으로 푼 문제 수 (스크래핑 + API): {streak}")
    print(f"전투력(power) : {power:.2f}")

    # ========================
    # (선택 사항) 추가 로그 출력
    # ========================
    plot_power_history()


if __name__ == "__main__":
    main()
