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

def get_lyrics(cmd):
  data = cmd.lower().split(' ')
  type = data.pop()
  song_name = '-'.join(data).capitalize()
  page = requests.get(f"https://genius.com/{song_name}-lyrics")
  soup = BeautifulSoup(page.content, 'html.parser')
  lyrics = soup.find(class_="lyrics").get_text()

  if type == 'full':
    print(lyrics)
  elif type == 'verse_1':
    verse_1 = ""
    for line in lyrics.splitlines():
      if '[Verse 2]' in line:
        break
      else:
        verse_1 += line + "\n"
    print(verse_1)
  elif type == 'verse_2':
    index = lyrics.splitlines().index('[Verse 2]')
    for i in lyrics.splitlines()[index:]:
      print(i)
  else:
    print("Something Went Wrong!")


# sia chandeleier (verse_1/verse_2/full)
cmd = str(input("Enter Song Name --> ")).lower()
get_lyrics(cmd)
