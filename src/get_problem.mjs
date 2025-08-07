import { HeaderGenerator } from 'header-generator';
import TurndownService from 'turndown';
import { parse } from 'node-html-parser';
import fs from 'fs-extra';
import { fileTypeFromBuffer } from 'file-type';

const turndownService = new TurndownService();

let headerGenerator = new HeaderGenerator({
    browsers: [
        { name: "firefox", minVersion: 90 },
        { name: "chrome", minVersion: 110 },
        "safari"
    ],
    devices: [
        "desktop"
    ],
    operatingSystems: [
        "windows"
    ]
});

const fetchHtmlWithCustomHeaders = async (url) => {
    try {
        const response = await fetch(url, {
            method: 'GET', // 요청의 종류를 설정합니다 (GET, POST 등)
            headers: headerGenerator.getHeaders()
        });

        if (!response.ok) {
            throw new Error(`HTTP error! status: ${response.status}`);
        }

        const html = await response.text();
        const root = parse(html);
        const want_delete = [root.querySelectorAll('#problem-lang-base64'), root.querySelectorAll('script'), root.querySelectorAll('#problem-info thead'), root.querySelectorAll('ul.problem-menu'), root.querySelectorAll('span.problem-label'), root.querySelectorAll('button.copy-button')];
        for (const cur of want_delete) {
            for (const item of cur) {
                item.set_content('');
            }
        }
        const sample_inputs = [];
        const sample_outputs = [];

        for (let idx = 1; idx <= 100; ++idx) {
            const id_input = 'sample-input-' + idx;
            const id_output = 'sample-output-' + idx;
            const cur_input = root.querySelector('#' + id_input) && root.querySelector('#' + id_input).innerHTML;
            const cur_output = root.querySelector('#' + id_output) && root.querySelector('#' + id_output).innerHTML;
            if (cur_input && cur_output) {
                sample_inputs.push(cur_input.trimEnd());
                sample_outputs.push(cur_output.trimEnd());
            } else {
                break;
            }
        }

        const contentDivs = root.querySelectorAll('div .container.content');
        if (contentDivs.length == 0) return '';
        const markdown = '# ' + turndownService.turndown(contentDivs[0].innerHTML);
        return {
            html: root,
            markdown,
            sample_inputs,
            sample_outputs,
            sample_cnt: sample_inputs.length,
        }
    } catch (error) {
        console.error('Error fetching the HTML:', error);
    }
};

// 디렉토리 생성 및 파일 작성
async function writeFile(filePath, content) {
    try {
        await fs.outputFile(filePath, String(content));
    } catch (error) {
        console.error('Error writing file:', error);
    }
}

async function saveAttachments(html, basePath) {
    // 정규식을 사용해 https://로 시작하는 URL 찾기
    const urlPattern = /https:\/\/(?:[a-zA-Z0-9-]+\.)+[a-zA-Z]{2,}(?:\/[^\s"'<>()]*)?/g;
    const urls = String(html).match(urlPattern);

    if (urls) {
        urls.forEach(async (url, index) => {
            try {
                const response = await fetch(url, {
                    method: 'GET', // 요청의 종류를 설정합니다 (GET, POST 등)
                    headers: headerGenerator.getHeaders()
                });
                if (!response.ok) throw new Error(`Failed to fetch ${url}: ${response.statusText}`);

                // 파일 내용을 버퍼로 가져오기
                const buffer = await response.arrayBuffer();

                // 파일 유형 및 확장자 추정
                const fileType = await fileTypeFromBuffer(buffer);
                let extension = fileType ? fileType.ext : 'bin'; // 파일 유형을 알 수 없을 경우 기본값 'bin'

                // 파일 이름 설정
                const fileName = `${index}.${extension}`;
                const filePath = `${basePath}/${fileName}`;

                // 파일 내용 저장
                await fs.outputFile(filePath, Buffer.from(buffer));
            } catch (error) {
                console.error(`Error fetching URL ${url}:`, error);
            }
        });
    } else {
        // console.log('No URLs found in the HTML.');
    }
}

function createTemplate(langs, problem_num, base) {
    for (const lang of langs) {
        const content = String(fs.readFileSync(`./src/template.${lang}`));
        const changed = content.replaceAll('BOJ_PROBLEM_NUMBER', problem_num);
        fs.outputFileSync(`${base}/solution/main.${lang}`, changed);
    }
    for (const lang of langs) {
        const content = String(fs.readFileSync(`./src/${lang}_test.sh`));
        const changed = content.replaceAll('BOJ_PROBLEM_NUMBER', problem_num);
        fs.outputFileSync(`${base}/${lang}_test.sh`, changed);
        fs.chmodSync(`${base}/${lang}_test.sh`, '755');
    }
}

async function savePageImage(url, path) {
    const browser = await puppeteer.launch({
        args: ['--no-sandbox'],
        headless: true
    });
    const page = await browser.newPage();
    const headers = headerGenerator.getHeaders();
    await page.setExtraHTTPHeaders(headers);
    await page.goto(url);
    await page.screenshot({ path: `${path}`, fullPage: true });
    await browser.close();
}

(async () => {
    const args = process.argv.slice(2);
    const problem_num = Number(args[0]);
    if (!problem_num) {
        console.error('Please provide the boj problem number!');
        return;
    }

    const ret = await fetchHtmlWithCustomHeaders('https://www.acmicpc.net/problem/' + problem_num);
    writeFile(`./boj/${problem_num}/desc.html`, ret.html);
    writeFile(`./boj/${problem_num}/desc.md`, ret.markdown);
    for (let i = 1; i <= ret.sample_cnt; ++i) {
        writeFile(`./boj/${problem_num}/input/${i}.txt`, ret.sample_inputs[i - 1]);
        writeFile(`./boj/${problem_num}/output/${i}.txt`, ret.sample_outputs[i - 1]);
    }
    saveAttachments(ret.markdown, `./boj/${problem_num}/attachments`);
    createTemplate(['cpp', 'py'], problem_num, `./boj/${problem_num}`);
    console.log('Done for collecting page, saving page screenshot...');
    // await savePageImage('https://www.acmicpc.net/problem/' + problem_num, `./boj/${problem_num}/desc.png`);
    console.log('All work ended.');
})();
