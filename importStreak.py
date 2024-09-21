import requests
from bs4 import BeautifulSoup
from selenium import webdriver
from selenium.webdriver.chrome.options import Options
from lxml import html
import re

# Chrome 옵션 설정
chrome_options = Options()
chrome_options.add_argument("--headless")  # 헤드리스 모드
chrome_options.add_argument("--no-sandbox")  # 샌드박스 비활성화 (Linux 환경)
chrome_options.add_argument("--disable-dev-shm-usage")  # /dev/shm 사용 안 함
chrome_options.add_argument("--disable-gpu")  # GPU 비활성화 (특히 Linux 환경에서 필요)

# 사용자의 solved.ac 프로필 URL
url = "https://solved.ac/profile/franj"
driver = webdriver.Chrome(options=chrome_options)
driver.get(url)
html = driver.page_source  # JavaScript가 실행된 후의 페이지 소스를 가져옴
soup = BeautifulSoup(html, 'html.parser')

div_elements = soup.find_all('div', class_='css-1midmz7')


# 찾은 모든 <div> 요소 확인
found_list=[]
for i, div_element in enumerate(div_elements):
    # print(f"div_element[{i}] 텍스트: {div_element.text.strip()}")
    # <b> 태그 찾기
    bold_tag = div_element.find('b')
    if bold_tag:
        bold_text = bold_tag.text.strip()
        # print(f"원본 텍스트: {bold_text}")
        
        # 정규 표현식을 사용하여 숫자 추출
        number = re.search(r'\d+', bold_text)
        if number:
            extracted_number = number.group()
            # print(f"추출된 숫자: {extracted_number}")
            found_list.append(extracted_number)
            
        else:
            print("숫자를 찾을 수 없습니다.")
    else:
        print("해당 div에 <b> 태그가 없습니다.")

print(found_list)
power = float(found_list[2]) ** (float(found_list[1]) * 1.15)
print(f"power : {power:.2f}")
    