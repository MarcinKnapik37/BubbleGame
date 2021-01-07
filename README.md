Dobry wieczór,

Przesyłam zaległą pracownię z bąbelkami.

Od prezentacji rano udało mi się dołączyć element przezroczystości
bąbelków. Nie wiem jednak dlaczego w jednym poziomym pasie (nieco
nad początkowym bąbelkiem) efekt transparentności powoduje powstawanie
artefaktów.

Ogólna obsługa gry:

Grę kompilujemy za pomocą komendy:
$ make

Przy wywołaniu podajemy dwa argumenty, pierwszy to wielkość
planszy (>= 5) a drugi reprezentuje losowe ziarno do programu.

na przykład:
$ ./Gra 8 10

- Kierowanie WASD
- Przycisk M uwalnia kursor muszy (można wtedy zmienić rozmiar okna)
- Przycisk C zmienia kamerę na zawieszoną pod sufitem.
- Przycisk H (jak również dotarcie do złotej bombelki)
powoduje zwiększenie liczby przeszkód

Kod w większości bazowany z tutorialu learnopenGL.

Pozdrawiam,
Marcin Knapik