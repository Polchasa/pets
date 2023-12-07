@echo off

REM Удаление файлов с расширениями, которые вы считаете ненужными
del /s /q *.user
del /s /q *.suo
del /s /q *.exe
del /s /q *.o
del /s /q Makefile*
del /s /q debug\*.*
del /s /q release\*.*

echo "Ненужные файлы удалены успешно."
