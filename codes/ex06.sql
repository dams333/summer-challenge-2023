WITH classesAvailable AS (
        SELECT
            class.classId AS classId
        FROM class
        WHERE (
            SELECT
                COUNT(schedule.classId)
            FROM schedule
            WHERE schedule.classId = class.classId
            AND schedule.day = DAYNAME('3961-05-12')
            AND schedule.hour = 15
        ) = 0
)

SELECT
    student.name AS NAME
    FROM onlineChat

    JOIN studentsChatsMap ON studentsChatsMap.chatId = onlineChat.chatId
    JOIN student ON student.studentId = studentsChatsMap.studentId

    -- Check chat creations in the last week
    WHERE onlineChat.createdAt > DATEADD('DAY', -7, CURRENT_DATE)

    -- Check user count = 7
    AND
    (
        SELECT
            COUNT(userCounter.chatId)
        FROM studentsChatsMap as userCounter

        WHERE userCounter.chatId = onlineChat.chatId

        GROUP BY userCounter.chatId
    ) = 7

    -- Check all user has grade > median
    AND
    (
        SELECT
            COUNT(userCounter.studentId)
        FROM studentsChatsMap as userCounter
        
        JOIN student as gradeVerifier
        ON gradeVerifier.studentId = userCounter.studentId

        WHERE userCounter.chatId = onlineChat.chatId
        AND gradeVerifier.avgGrade >
        (
            SELECT MEDIAN(avgGrade)
            FROM student
        )
    ) = 7

    -- Check 3 users are not in class
    AND
    (
        SELECT
            COUNT(userCounter.studentId)
        FROM studentsChatsMap as userCounter

        JOIN student as studentObj
        ON studentObj.studentId = userCounter.studentId

        WHERE userCounter.chatId = onlineChat.chatId
        AND studentObj.classId IN (SELECT classId FROM classesAvailable)
    ) >= 3

    -- Check 2 are bigs
    AND
    (
        SELECT
            COUNT(userCounter.studentId)
        FROM studentsChatsMap as userCounter

        JOIN student as studentObj
        ON studentObj.studentId = userCounter.studentId

        WHERE userCounter.chatId = onlineChat.chatId
        AND studentObj.height > 320
    ) = 2

    -- Check 3 in the same room
    AND
    (
        SELECT COUNT(*)
        FROM (
            SELECT
                userCounter.chatId as chatId,
                COUNT(studentObj.bedroomId) AS inSameBedroom
            FROM studentsChatsMap AS userCounter

            JOIN student AS studentObj ON studentObj.studentId = userCounter.studentId

            GROUP BY studentObj.bedroomId, userCounter.chatId
        ) AS subquery
        WHERE subquery.chatId = onlineChat.chatId
        AND subquery.inSameBedroom = 3
    ) > 0

    -- Check one has long time in chemistry room
    AND
    (
        SELECT
            MAX(TIMESTAMPDIFF(MINUTE, roomAccessHistory.enteredAt, roomAccessHistory.exitedAt))
        FROM studentsChatsMap as userCounter
        
        JOIN roomAccessHistory
        ON roomAccessHistory.studentId = userCounter.studentId

        JOIN room
        ON room.roomId = roomAccessHistory.roomId

        WHERE userCounter.chatId = onlineChat.chatId
        AND room.roomName = 'Chemistry supply room'
    ) > 60

    AND 
    (
        SELECT
            COUNT(userCounter.studentId)
        FROM studentsChatsMap as userCounter

        JOIN student as studentObj
        ON studentObj.studentId = userCounter.studentId

        WHERE userCounter.chatId = onlineChat.chatId
        AND LOCATE('w', LOWER(studentObj.name)) != 0
        AND LOCATE('m', LOWER(studentObj.name)) != 0
    ) > 0

    ORDER BY studentsChatsMap.chatId ASC
