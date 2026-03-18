<%@page contentType="text/html" pageEncoding="UTF-8"%>
<%@ taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core"%>

<!DOCTYPE html>
<html lang="ro">
<head>
    <meta charset="UTF-8">
    <title>Adaugă Proces</title>
    <link rel="stylesheet" href="css/style.css?v=1">
</head>

<body class="page-justice">

<div class="justice-card">

    <h1 class="justice-title">⚖️ Adaugă Proces ⚖️</h1>

    <form action="ProceseController" method="GET">

        <label><b>Număr dosar</b></label><br>
        <input type="text" name="Numar_Dosar" class="justice-btn">
        <br>

        <label><b>Tip proces</b></label><br>
        <input type="text" name="Tip_Proces" class="justice-btn">
        <br>

        <label><b>Stadiu</b></label><br>
        <input type="text" name="Stadiu" class="justice-btn">
        <br>

        <label><b>Data înregistrării</b></label><br>
        <input type="date" name="Data_Inregistrarii" class="justice-btn">
        <br>

        <label><b>Denumire</b></label><br>
        <input type="text" name="Denumire" class="justice-btn">
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
        	name="adaugaProces"
        	class="justice-btn success">
    		➕ Adaugă
		</button>

    </form>

    <form action="ProceseController" method="POST">
        <button type="submit"
        	name="afiseazaProcese"
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
