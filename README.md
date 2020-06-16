# AKISO
Zadania wykonane podczas kursu Architektura Komputerów i Systemy Operacyjne
## Lista 3
6. Napisz program w języku C, który wykorzystując sekwencje Esc (ang. escape sequences) standardu ANSI wyświetli na ekranie napis "Hello, World!", po kolei we wszystkich dostępnych przez terminal kolorach. Czy terminal może wyświetlić 256 kolorów?
7. Napisz potok poleceń (w skrypcie), który zamienia wszystkie nazwy plików w danym katalogu (bez podkatalogów) na małe litery, czyli wszystkie duże litery występujące w nazwach plików zostaną zamienione na małe, a małe litery pozostają oczywiście dalej małe. Skrypt powinien działać poprawnie na takich nazwach plików jak " ABC DEF", "-AbC aBc" i "--ABC DEF". Podane nazwy plików proszę zakładać w konsoli korzystając z polecenia touch.

## Lista 4
1. Napisz skrypt w Bashu, który co sekundę pokazuje następujące informacje o systemie:
* Aktualną i średnią prędkość przesyłania danych po interfejsach sieciowych (odczytaj i zinterpretuj /proc/net/dev oraz wyświetl w B, KB lub MB w zależność od aktualnej prędkości)
* Jak długo system jest uruchomiony w dniach, godzinach, minutach i sekundach (/proc/uptime)
* Aktualny stan baterii w procentach (/sys/class/power_supply/BAT0/uevent)
* Obciążenie systemu /proc/loadavg
Skrypt prezentuje "graficznie" historię poprzednich pomiarów np. prosty wykres słupkowy. Przykładowe programy z wykresami s-tui lub bmon. Można wykorzystać inne znaki w UTF-8. Zobacz też informacje o komendzie tput np. link i/lub link.
2. Napisz skrypt w Bashu, który pokazuje informacje o wszystkich procesach (podobne jak program ps). Wykorzystaj system plików procfs (standardowo w systemie Linux montowanym w katalogu /proc) do pobrania informacji o procesach np. cat /proc/1/status wyświetla informacje o procesie 1. Dodatkowo wyświetl informację ile proces ma otwartych plików.
3. Napisz skrypt w Bashu wykorzystujący REST API do pobierania danych z dwóch przykładowych źródeł np. Internet Chuck Norris Database (ICNDb) i The Cat API. Do zapytań RESTowych wykorzystaj curl lub wget do parsowania JSONa wystarczy program jq (pacman -S jq), dla osób korzystających z formatu XML dostępny jest program xmllint (pacman -S libxml2). Po uruchomieniu skryptu na ekranie pokaż obraz z bazy 'The Cat API' wykorzystując np. program img2txt (pacman -S libcaca) lub catimg oraz poniżej wyświetl losowy cytat z bazy Chucka Norrisa.
4. Napisz skrypt w Bashu, który przechowuje historię zmian podanej strony z internetu i powiadamia użytkownika w momentach zmian na stronie (do powiadamiania można wykorzystać komendę xmessage, zenity lub echo z terminala i wyświetlić zmiany). Przykładowe wywołanie programu:
$ ./webtrace.sh "http://ki.pwr.edu.pl" 600, gdzie pierwszym parametrem jest adres śledzonej strony, a drugim parametrem jest czas w sekundach co jaki strona będzie pobierana i sprawdzana czy nastąpiła zmiana, czyli w powyższym przykładzie strona http://ki.pwr.edu.pl będzie sprawdzana co 10 minut.
Wskazówka: Do pobrania strony można wykorzystać np. lynx -dump http://ki.pwr.edu.pl (man lynx, instalacja pacman -S lynx) lub links (man links, instalacja pacman -S links) lub w3m (man w3m, instalacja pacman -S w3m) lub ... . Do sprawdzania zmian na stronie: diff (man diff), ... . Do pamiętania historii można wykorzystać repozytorium git, instalacja pacman -S git.

## Lista 5
1. Napisz program w języku C, który uruchomi powłokę (Bash) z prawami roota. Po kompilacji programu można ustawić (z poziomu roota) dowolne atrybuty (np. patrz SUID). Następnie już z poziomu dowolnego użytkownika uruchamiając program uruchamia się konsola administratora, podobnie jak sudo /bin/bash (bez wprowadzania hasła).
2. Napisz w języku C programy testujące, które odpowiedzą na następujące pytania:
* Czy można napisać program do obsługi wszystkich sygnałów (patrz kill -l)? Napisz program prezentujący odpowiedź.
* Czy jest możliwe wysłać sygnał SIGKILL, lub inny do procesu init (PID 1) czyli np. kill -9 1 (nawet będąc rootem)?
* Czy sygnały są kolejkowane? Np. napisz program testowy wysyłający wiele razy do danego procesu sygnał (np. SIGUSR1) i zobacz czy wszystkie dotarły.
3. Zaimplementuj w języku C prostą wersję powłoki o nazwie lsh. Jak prawdziwa powłoka, lsh odczytuje linię ze standardowego wejścia i przeszukuje ścieżki ze zmiennej PATH (inaczej mówiąc zamiast execve wykonuje execvp) i wykonuje podany program. Proszę pamiętać o ustawieniu argumentów wykonywanej komendy. Jeśli linia kończy się znakiem (&), wtedy lsh powinien nie czekać aż komenda zostanie skończona i od razu wrócić. W innym przypadku lsh powinien zaczekać, aż program wykona się. lsh powinien skończyć swoje działanie naciskając klawisze Control+D lub pisząc exit. Zmieniamy katalogi przez wpisanie komendy cd. Komendy cd oraz exit to komendy wbudowane. Uwaga: Procesy uruchomione w tle, które się zakończyły mogą stać się procesami 'zombi', rozwiąż ten problem w lsh.
4. Zaimplementuj w programie lsh z poprzedniego zadania potoki | (ang. pipe) oraz przekierowanie standardowego wejścia (<), wyjścia (>) oraz wyjścia błędu (2>). Wskazówka: Zobacz program lssort.c. Ponadto Ctrl-C przerywa wykonywanie programu w powłoce (nie samej powłoki oraz zadań wykonywanych w tle).
6. Napisz moduł dla Linuksa w języku C, który dodaje nowe wywołanie systemowe i działa na aktualnej wersji Ubuntu i/lub Arch Linux. Nowe wywołanie systemowe wyświetla tylko napis "Hello World!" (wykorzystując printk). Napisz program w języku C, który testuje nowe wywołanie systemowe. Uwaga: Pamiętaj, że dodanie nowego wywołania, aby rozszerzyć funkcjonalność jądra nie powinno być stosowane jako pierwszy wybór! Potraktuj to zadanie tylko jako ćwiczenie.

## Lista 6
1. Napisz w języku C własną implementacje funkcji printf i scanf (nazwijmy je myprintf i myscanf). Funkcje nie mogą wykorzystywać, żadnych funkcji bibliotecznych (atoi, fprintf, fscanf itp.) oraz makr va_start, va_arg i va_end (np. możesz skorzystać z wyjaśnienia tutaj oraz patrz X86 calling conventions i dokładniej cdecl) oraz można wykorzystać wywołania systemowe read i write z odpowiednim standardowym deskryptorem. Program należy skompilować na maszynę 32-bitową tzn. gcc -m32 np. dla 64-bitowego systemu ArchLinux trzeba zainstalować pakiet gcc-multilib z repozytorium multilib. W funkcjach wystarczy zaimplementować "%s", "%d", "%x" i "%b", gdzie w naszej implementacji "%s" wyświetla ciąg znaków, "%d" liczbę w systemie dziesiętnym, "%x" liczbę w systemie szesnastkowych oraz "%b" liczbę w systemie binarnym.
2. Napisz w języku C wielowątkową wersję mnożenia macierzy boolowskich. Program powinien pobierać z linii komend wielkość macierzy (wypełniać ją losowymi wartościami 0 lub 1, patrz man 3 random) oraz liczbę wątków, która powinna zostać uruchomiona do mnożenia. Zaimplementuj program tak, że każdy wątek pracuje na osobnym wierszu, jeśli jeden skończy pracę to dalej pracuje na następnym wolnym wierszu oraz pamiętaj, że pojedynczy iloczyn skalarny (wiersz razy kolumna) może zostać ustalony wcześniej nawet po pierwszej koniunkcji. Pamiętaj, że przy dostępie do zmiennych współdzielonych mogą wystąpić wyścigi!

## Lista 7
1. Wykorzystując program z wykładu, napisz program w asemblerze dla procesora 6502, który wykonuje szybkie mnożenie (wykorzystujące przesunięcia bitowe, nie mnożenie przez "dodawanie"). Wytłumacz dokładnie zasadę jego działania. Pokaż jak program wykonuje się w emulatorze emu6502 (paczka emu6502 + xasm - linux32, linux64, win32). Pokaż również jak można wykorzystać opcje -v oraz -m emulatora.
2. Napisz program w asemblerze x86 (32-bit), który pobiera ze standardowego wejścia liczbę N oraz drukuje na standardowe wyjście

1 \
1 2 \
1 2 3 \
1 2 3 4 \
... \
1 2 3 4 5 ... N\
Uwaga: można wykorzystać tylko wywołania systemowe (bez funkcji z bibliotek).

3. Napisz program w asemblerze x86 (32-bit) z wykorzystaniem koprocesora matematycznego, który potrafi obliczać następujące funkcje
* sinh(x) = (e^x − e^(−x))/2
* sinh^(−1)(x) = ln(x+(x^2+1)^0.5)\
Program pobiera ze standardowego wejścia liczbę x, wykorzystując koprocesor matematyczny oblicza wynik (na liczbach zmiennoprzecinkowych) i wysyła na standardowe wyjście.
4. Napisz w asemblerze x86 program rysujący zbiór Mandelbrota (patrz wykład z 2019.11.28 slajdy 43-46). Inicjalizację trybu graficznego można przeprowadzić wykorzystując kod boot sektora.
5. Napisz program w asemblerze dla procesora ARM, który oblicza największy wspólny dzielnik dwóch liczb. Pobieraj dwie liczby, ze standardowego wejścia i wysyłaj wynik na standardowe wyjście.
6. Wykorzystując rozkazy MMX, bibliotekę SDL oraz wzorując się na przykładzie z wykładu fade, napisz program wykonujący płynne przenikanie jednego obrazu graficznego w drugi. Postaraj się jak najbardziej zoptymalizować program (czyli uzyskać jak największe FPS).
7. Napisz program w asemblerze x86 (32-bit) z rozkazami SIMD (SSE2), który liczy silnię n! na liczbach 128 bitowych. Zauważ, że 128-bitowe rejestry XMM0,...,XMM7 od wersji SSE2, mogą być traktowane jako dwa 64-bitowe liczby całkowite lub cztery 32-bitowe itd. Liczba n pobierana jest z argumentów argc, argv (lub ze standardowego wejścia) oraz wynik wysyłany jest na standardowe wyjście.
8. Wzorując się na szybkim mnożeniu dla procesora 6502 przedstawionym na wykładzie, napisz program, który wykonuje dzielenie z resztą liczby szesnastobitowej przez ośmiobitową (czyli wraca wynik dzielenia oraz resztę). Staraj się zrobić dzielenie o najmniejszej złożoności obliczeniowej. Wskazówka: skorzystaj m. in. z instrukcji LSR, ROL i SBC
