<%@page contentType="text/html" pageEncoding="UTF-8"%>
<%@ taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core"%>

<!DOCTYPE html>
<html lang="ro">
<head>
    <meta charset="UTF-8">
    <title>Adaugă judecător</title>
    <link rel="stylesheet" href="css/style.css?v=1">
</head>

<body class="page-justice">

<div class="justice-card">

    <h1 class="justice-title">⚖️ Adaugă judecător ⚖️</h1>

    <form action="JudecatoriController" method="GET">

        <label><b>Nume judecător</b></label><br>
        <input type="text" name="Nume_Judecator" class="justice-btn">

        <br>

        <label><b>Prenume judecător</b></label><br>
        <input type="text" name="Prenume_Judecator" class="justice-btn">

        <br>

        <label><b>CNP</b></label><br>
        <input type="text" name="CNP" class="justice-btn">

        <br>

        <label><b>Data nașterii</b></label><br>
        <input type="date" name="Data_Nasterii" class="justice-btn">

        <br>

        <label><b>Grad</b></label><br>
        <input type="text" name="Grad" class="justice-btn">

        <br>

        <c:if test="${not empty eroare}">
            <p style="color:red; font-weight:bold; text-align:center;">
                ${eroare}
            </p>
        </c:if>
		
		<c:if test="${not empty succes}">
    		<p style="color:green; font-weight:bold; font-size:20px; text-align:center;">
        	${succes}
    		</p>
		</c:if>

        <button type="submit"
        name="adaugaJudecator"
        class="justice-btn success">
    ➕ Adaugă
</button>

    </form>

    <form action="JudecatoriController" method="POST">
        <button type="submit"
        name="afiseazaJudecatori"
        class="justice-btn secondary">
    📑 Afișează
</button>
    </form>

    <button type="button"
            class="justice-btn secondary"
            onclick="location.href='index.html'">
        	🏠 Acasă
    		</button>
    

</div>

</body>
</html>