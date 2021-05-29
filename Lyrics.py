"""
[!] Coded By :- Dhruv Lohar
[!] Written On :- 17 Nov, 2020
[!] Follow the steps to run the scripts :
--> pip install requests
--> pip install beautifulsoup4
--> python Lyrics.py
"""

import requests
from bs4 import BeautifulSoup

class Lyrics:
    def __init__(self, query):
        self.query = query.replace(' ', '+')
        self.get_lyrics()
    
    def get_seach_results(self):
        response = requests.get(f'https://search.azlyrics.com/search.php?q={self.query}')
        page = BeautifulSoup(response.content, 'html.parser')
        links = [link['href'] for link in page.find_all('a')]
        for link in links:
            if self.query.split('+')[0] in link:
                return link
                break

    def get_lyrics(self):
        url = self.get_seach_results()
        singer = url.split('/')[4]
        response = requests.get(url)
        page = BeautifulSoup(response.content, 'html.parser')
        lyrics = page.find('div', class_=None, id=None)
        print(lyrics.get_text())
        print(f'By {singer.upper()}')

song = input('Enter Song Name --> ')
lyrics = Lyrics(song)
