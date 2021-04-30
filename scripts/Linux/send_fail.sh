echo.
echo Send fail report ...
echo.
curl -F document=@"fail.build" https://api.telegram.org/bot1796168405:AAGOO4O_gydbNEY-J96KspPdmlsoPFlrVNY/sendDocument?chat_id=546264605 > /dev/null 2>&1
