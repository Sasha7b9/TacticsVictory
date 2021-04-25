#data=$(cat build.log)
#curl -X POST \
#,    -F document=@"build.log" '{"chat_id": "546264605"
curl -F document=@"build.log" https://api.telegram.org/bot1796168405:AAGOO4O_gydbNEY-J96KspPdmlsoPFlrVNY/sendDocument?chat_id=546264605
