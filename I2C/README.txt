19.12.2025 - Initial Commit
Funkcje obsługujące I2C napisane i przetestowane 
TO-DO: Usprawnienie funkcji; pozbycie się opóźnienień, dodanie walidacji

22.12.2025 - Upgrade
-----------NIE PRZETESTOWANO-----------
Dodano alternatywną obsługę opóźnień poprzez timer. Funkcję należy umieścić w timerze który będzie wywoływał funkcję co określony czas. Okres ten ma być równy okresowi podanemu przez producenta danego peryferium odnośnie częstości wysłania ramek.