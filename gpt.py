import re
import os
import requests
from bs4 import BeautifulSoup
from langchain_openai import ChatOpenAI
from langchain_core.output_parsers import StrOutputParser
from langchain_core.prompts import PromptTemplate

# 환경 변수에서 OpenAI API 키 가져오기
openai_api_key = os.getenv("OPENAI_API_KEY")
if not openai_api_key:
    raise ValueError("환경 변수에 OPENAI_API_KEY가 설정되지 않았습니다.")
os.environ["OPENAI_API_KEY"] = openai_api_key

# 출력 파서 초기화
parser = StrOutputParser()


import requests
from bs4 import BeautifulSoup


def get_problem_description(problem_number):
    url = f"https://www.acmicpc.net/problem/{problem_number}"
    headers = {
        "User-Agent": "Mozilla/5.0 (Windows NT 10.0; Win64; x64) "
        "AppleWebKit/537.36 (KHTML, like Gecko) "
        "Chrome/90.0.4430.93 Safari/537.36",
        "Accept-Language": "en-US,en;q=0.9",
        "Accept": "text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8",
        "Referer": "https://www.google.com/",
        "Connection": "keep-alive",
    }

    session = requests.Session()
    response = session.get(url, headers=headers)

    if response.status_code == 403:
        raise ValueError(
            f"문제 번호 {problem_number}에 해당하는 페이지에 접근이 거부되었습니다. 상태 코드: {response.status_code}"
        )
    elif response.status_code != 200:
        raise ValueError(
            f"문제 번호 {problem_number}에 해당하는 페이지를 가져올 수 없습니다. 상태 코드: {response.status_code}"
        )

    soup = BeautifulSoup(response.text, "html.parser")

    # 문제 제목 추출
    title_tag = soup.find("span", id="problem_title")
    if not title_tag:
        raise ValueError("문제 제목을 찾을 수 없습니다.")
    title = title_tag.get_text(strip=True)

    # 문제 설명 추출
    description_div = soup.find("div", id="problem_description")
    if not description_div:
        raise ValueError("문제 설명을 찾을 수 없습니다.")
    description = description_div.get_text(separator="\n", strip=True)

    # 입력 설명 추출
    input_div = soup.find("div", id="problem_input")
    problem_input = (
        input_div.get_text(separator="\n", strip=True)
        if input_div
        else "입력 설명을 찾을 수 없습니다."
    )

    # 출력 설명 추출
    output_div = soup.find("div", id="problem_output")
    problem_output = (
        output_div.get_text(separator="\n", strip=True)
        if output_div
        else "출력 설명을 찾을 수 없습니다."
    )

    # 샘플 입력과 출력 추출
    sample_inputs = []
    sample_outputs = []

    for idx in range(1, 101):  # 최대 100개의 샘플을 시도
        input_id = f"sample-input-{idx}"
        output_id = f"sample-output-{idx}"

        input_tag = soup.find(id=input_id)
        output_tag = soup.find(id=output_id)

        if input_tag and output_tag:
            # `<pre>` 태그 내의 텍스트를 추출
            input_pre = input_tag.find("pre")
            output_pre = output_tag.find("pre")

            if input_pre and output_pre:
                sample_input = input_pre.get_text(separator="\n", strip=True)
                sample_output = output_pre.get_text(separator="\n", strip=True)

                sample_inputs.append(sample_input)
                sample_outputs.append(sample_output)
            else:
                # `<pre>` 태그가 없을 경우 전체 텍스트 추출
                sample_input = input_tag.get_text(separator="\n", strip=True)
                sample_output = output_tag.get_text(separator="\n", strip=True)

                sample_inputs.append(sample_input)
                sample_outputs.append(sample_output)
        else:
            # 더 이상 샘플이 없으면 루프 종료
            break

    # 샘플 입력과 출력 포맷팅
    samples = []
    for i in range(max(len(sample_inputs), len(sample_outputs))):
        sample = ""
        if i < len(sample_inputs):
            sample += f"샘플 입력 {i+1}:\n{sample_inputs[i]}"
        if i < len(sample_outputs):
            sample += f"\n샘플 출력 {i+1}:\n{sample_outputs[i]}"
        samples.append(sample)

    samples_formatted = "\n\n".join(samples)

    full_description = (
        f"문제 번호: {problem_number}\n"
        f"문제 제목: {title}\n\n"
        f"문제 설명:\n{description}\n\n"
        f"입력:\n{problem_input}\n\n"
        f"출력:\n{problem_output}\n\n"
        f"예제:\n{samples_formatted}"
    )
    return full_description


# 코드 블록 추출 함수 정의 (Python과 C++ 지원)
def extract_code(response_text):
    # ```언어\n코드``` 패턴으로 코드 블록 추출
    code_blocks = re.findall(r"```(\w+)?\n(.*?)```", response_text, re.DOTALL)
    extracted_codes = []
    for lang, code in code_blocks:
        lang = lang.lower() if lang else "txt"  # 언어가 명시되지 않은 경우 'txt'로 설정
        # 언어에 따른 파일 확장자 결정
        if lang in ["python", "py"]:
            ext = "py"
        elif lang in ["cpp", "c++", "c"]:
            ext = "cpp"
        elif lang in ["javascript", "js"]:
            ext = "js"
        else:
            ext = "txt"  # 기타 언어는 텍스트 파일로 저장
        extracted_codes.append((ext, code))
    return extracted_codes


# 문제 번호 입력 받기
problem_number = input("문제 번호를 입력하세요 (예: 3176): ").strip()
if not problem_number.isdigit():
    raise ValueError("문제 번호는 숫자여야 합니다.")

# 문제 설명 스크랩
try:
    problem_description = get_problem_description(problem_number)
    print(f"문제 번호 {problem_number}의 설명을 성공적으로 가져왔습니다.")
    print(problem_description)
except ValueError as ve:
    print(f"오류 발생: {ve}")
    exit(1)

# 프롬프트 템플릿 정의
prompt_template = PromptTemplate.from_template(
    "당신은 coding 전문가입니다. 다음 문제에 대해 C++로 풀어주세요 : {subject}"
)

# ChatOpenAI 초기화
llm = ChatOpenAI(
    model_name="gpt-4o",  # 사용 가능한 모델로 변경
    max_tokens=4096,
    temperature=0,
)

# 체인 구성: 프롬프트 -> LLM -> 파서
chain = prompt_template | llm | parser

# 체인 실행: 문제 설명을 'subject'에 전달
try:
    response = chain.invoke({"subject": problem_description})
    print("OpenAI API로부터 응답을 성공적으로 받았습니다.")
except Exception as e:
    print(f"OpenAI API 호출 중 오류 발생: {e}")
    exit(1)

# 디버깅을 위해 응답 내용 출력
print("응답 내용:\n", response)

# 코드 블록 추출
code_blocks = extract_code(response)

if not code_blocks:
    print("코드 블록을 찾을 수 없습니다.")
else:
    for idx, (ext, code) in enumerate(code_blocks):
        # 파일 이름 설정: 단일 코드 블록인 경우 'solution.py' 또는 'solution.cpp'
        # 다중 코드 블록인 경우 'solution_1.py', 'solution_2.cpp' 등
        if len(code_blocks) == 1:
            output_file = f"solution.{ext}"
        else:
            output_file = f"solution_{idx + 1}.{ext}"

        # 코드 내용을 파일로 저장
        with open(output_file, "w", encoding="utf-8") as file:
            file.write(code)

        print(f"코드가 {output_file} 파일에 저장되었습니다.")
