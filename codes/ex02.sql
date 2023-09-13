SELECT 
    agent.name AS NAME,
    COUNT(agent.name) AS SCORE

    FROM mutant

    JOIN agent ON agent.agentId = mutant.recruiterID

    GROUP BY agent.name

    ORDER BY SCORE DESC
    LIMIT 10
