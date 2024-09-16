import { HeaderGenerator } from 'header-generator';
import TurndownService from 'turndown';
import { parse } from 'node-html-parser';
import fs from 'fs-extra';
import { fileTypeFromBuffer } from 'file-type';
import puppeteer from 'puppeteer';

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

async function submit(url, path) {
    const browser = await puppeteer.launch({
        args: ['--no-sandbox'],
        headless: true
    });
    const page = await browser.newPage();
    const myHeaders = headerGenerator.getHeaders();
    let cookies = [];
    const cookieFilePath = './cookie.txt';
    try {
        const cookieString = await fs.readFile(cookieFilePath, 'utf8');
        cookies = cookieString.split('; ').map(cookie => {
            const [name, value] = cookie.split('=');
            return {
                name: name.trim(),
                value: value.trim(),
                domain: '.acmicpc.net' // 쿠키의 도메인을 설정해야 합니다.
            };
        });
    } catch (err) {
        console.error('Error reading cookie file:', err);
    }

    console.log(cookies);
    console.log(myHeaders);

    await page.setExtraHTTPHeaders(myHeaders);

    // 페이지에 쿠키를 설정합니다.
    try {
        await page.setCookie(...cookies);
    } catch (err) {
        console.error('Error setting cookies:', err);
    }

    await page.goto(url);

    await page.screenshot({ path: `./test.png`, fullPage: true });

    const className = '.CodeMirror-code'; // 대기할 클래스 이름
    await page.waitForSelector(className, { timeout: 10000 }); // 10초 대기 (기본값은 무한대기)

    const currentCookies = await page.cookies();
    console.log(currentCookies); // 현재 설정된 쿠키 확인

    const source_code = await fs.readFile(path);
    await page.evaluate((source_code) => {
        document.querySelector('.CodeMirror').CodeMirror.setValue(source_code);
    }, String(source_code));
    await new Promise(resolve => setTimeout(resolve, 1500));
    await page.screenshot({ path: `./test2.png`, fullPage: true });

    console.log('Submitting...');
    await page.evaluate(() => {
        document.querySelector('#submit_form').submit();
    });
    await new Promise(resolve => setTimeout(resolve, 3000));
    await page.screenshot({ path: `./test3.png`, fullPage: true });
    //await page.click('#submit_button');
    // const currentCookies = await page.cookies();
    // console.log(currentCookies); // 현재 설정된 쿠키 확인
    await browser.close();
}

(async () => {
    const args = process.argv.slice(2);
    const problem_num = Number(args[0]);
    if (!problem_num) {
        console.error('Please provide the boj problem number!');
        return;
    }
    console.log('Submiting... (now only supports cpp)');
    await submit('https://www.acmicpc.net/submit/' + problem_num, `./boj/${problem_num}/solution/main.cpp`);
    console.log('All work ended.');
})();
