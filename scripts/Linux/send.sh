data=$(cat build.log)
curl -X POST \
    -H 'Content-Type: application/json' \
    -d '{"chat_id": "546264605", "text": "succesefull build" , "disable_notification": false}' \
    https://api.telegram.org/bot1796168405:AAGOO4O_gydbNEY-J96KspPdmlsoPFlrVNY/sendMessage
