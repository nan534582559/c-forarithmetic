from bs4 import BeautifulSoup
import requests, sys
 
"""
类说明:下载《笔趣看》网小说《一念永恒》
Parameters:
    无
Returns:
    无
Modify:
    2017-09-13
"""
class downloader(object):
 
    def __init__(self):
        self.server = 'http://kaijiang.500.com'
        self.target = 'http://kaijiang.500.com/shtml/dlt/18086.shtml'
        self.names = []            #存放章节名
        self.urls = []            #存放章节链接
        self.nums = 0            #章节数
 
    """
    函数说明:获取下载链接
    Parameters:
        无
    Returns:
        无
    Modify:
        2017-09-13
    """
    def get_download_url(self):
        req = requests.get(url = self.target)
        html = req.text
        div_bf = BeautifulSoup(html)
        div = div_bf.find_all('div', class_ = 'iSelectList')
        a_bf = BeautifulSoup(str(div[0]))
        a = a_bf.find_all('a')
        self.nums = len(a)                                #剔除不必要的章节，并统计章节数
        for each in a:
            self.names.append(each.string)
            self.urls.append(each.get('href'))
            print(each.get('href'))
 
    """
    函数说明:获取章节内容
    Parameters:
        target - 下载连接(string)
    Returns:
        texts - 章节内容(string)
    Modify:
        2017-09-13
    """
    # def get_contents(self, target):
        # req = requests.get(url = target)
        # html = req.text
        # bf = BeautifulSoup(html)
        # texts = bf.find('table', class_ = 'kj_tablelist02')
        # textTd = texts.find_all('td')
        # num = len(textTd)
        # print(textTd[5].text)
        # return textTd[5].text
        
    def get_contents(self, target):
        req = requests.get(url = target)
        html = req.text
        bf = BeautifulSoup(html)
        texts = bf.find_all('div', class_ = 'ball_box01')
        texts = texts[0].text.replace('\xa0'*8,' ')
        texts = texts.replace('\n',' ')
        print(texts)
        return texts
 
    """
    函数说明:将爬取的文章内容写入文件
    Parameters:
        name - 章节名称(string)
        path - 当前路径下,小说保存名称(string)
        text - 章节内容(string)
    Returns:
        无
    Modify:
        2017-09-13
    """
    def writer(self, name, path, text):
        write_flag = True
        with open(path, 'a', encoding='utf-8') as f:
            f.write(name + ' ')
            f.writelines(text)
            f.write('\n')
 
if __name__ == "__main__":
    dl = downloader()
    dl.get_download_url()
    print('bengin:')
    print(dl.nums)
    for i in range(dl.nums):
        dl.writer(dl.names[i], 'list.txt', dl.get_contents(dl.urls[i]))
        #sys.stdout.write("  已下载:%.3f%%" %  float(i/dl.nums) + '\r')
        sys.stdout.flush()
    print('end;')