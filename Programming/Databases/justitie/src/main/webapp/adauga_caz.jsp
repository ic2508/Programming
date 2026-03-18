<%@page import="DAOImpl.ProceseDaoImpl"%>
<%@page import="DAOImpl.JudecatoriDaoImpl"%>
<%@page import="pojo.Procese"%>
<%@page import="pojo.Judecatori"%>
<%@page import="java.util.List"%>
<%@page contentType="text/html; charset=UTF-8" pageEncoding="UTF-8"%>

<%
    // IMPORTANT: Codul JSP NU trebuie să lase output înainte de <html>
    JudecatoriDaoImpl judecatorDaoImpl = new JudecatoriDaoImpl();
    ProceseDaoImpl procesDaoImpl = new ProceseDaoImpl();

    List<Judecatori> listaJudecatori = judecatorDaoImpl.afiseazaJudecatori();
    List<Procese> listaProcese = procesDaoImpl.afiseazaProcese();

    request.setAttribute("listaJudecatori", listaJudecatori);
    request.setAttribute("listaProcese", listaProcese);
%>

<!DOCTYPE html>
<html lang="ro">
<head>
    <meta charset="UTF-8">
    <title>Adaugă caz</title>

    <link rel="stylesheet" href="css/style.css?v=123">
    <%@ taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core"%>
</head>

<body class="page-justice">

<div class="justice-card">

    <h1 class="justice-title">⚖️ Adaugă caz ⚖️</h1>

    <form action="CazuriController" method="POST">

        <label><b>Judecător</b></label><br>
        <select name="ID_Judecator" class="justice-btn">
            <c:forEach items="${listaJudecatori}" var="judecatori">
                <option value="${judecatori.ID_Judecator}">
                    ${judecatori.ID_Judecator}, ${judecatori.nume_Judecator},
                    ${judecatori.prenume_Judecator}, ${judecatori.CNP}
                </option>
            </c:forEach>
        </select>

        <br>
        
        <label><b>Proces</b></label><br>
        <select name="ID_Proces" class="justice-btn">
            <c:forEach items="${listaProcese}" var="procese">
                <option value="${procese.ID_Proces}">
                    ${procese.ID_Proces}, ${procese.numar_Dosar},
                    ${procese.tip_Proces}, ${procese.stadiu}
                </option>
            </c:forEach>
        </select>

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
        name="adaugaCaz"
        class="justice-btn success">
    ➕ Adaugă
</button>

    </form>

    <form action="CazuriController" method="POST">
        <button type="submit"
        name="afiseazaCazuri"
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
