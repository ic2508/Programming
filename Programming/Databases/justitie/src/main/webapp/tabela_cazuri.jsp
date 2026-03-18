<%@page import="DAOImpl.ProceseDaoImpl"%>
<%@page import="DAOImpl.JudecatoriDaoImpl"%>
<%@page import="pojo.Procese"%>
<%@page import="pojo.Judecatori"%>
<%@page import="pojo.Cazuri"%>
<%@page import="java.util.List"%>
<%@ taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core"%>
<%@page contentType="text/html" pageEncoding="UTF-8"%>

<%
    JudecatoriDaoImpl judecatorDaoImpl = new JudecatoriDaoImpl();
    ProceseDaoImpl procesDaoImpl = new ProceseDaoImpl();

    List<Judecatori> listaJudecatori = judecatorDaoImpl.afiseazaJudecatori();
    List<Procese> listaProcese = procesDaoImpl.afiseazaProcese();

    request.setAttribute("listaJudecatori", listaJudecatori);
    request.setAttribute("listaProcese", listaProcese);
%>

<!DOCTYPE html>
<html>
<head>
    <meta charset="UTF-8">
    <title>Tabela cazuri</title>
    <link rel="stylesheet" href="css/style.css?v=1">

    <script src="https://ajax.googleapis.com/ajax/libs/jquery/1.12.4/jquery.min.js"></script>

    
</head>

<body class="page-justice">

<div class="justice-card" style="width:90%; max-width:1200px;">

    <h1 class="justice-title">📑 Tabela cazuri</h1>

    <c:if test="${not empty eroare}">
        <p style="color:red; font-weight:bold; text-align:center; font-size:18px;">
            ${eroare}
        </p>
    </c:if>

    <c:if test="${not empty succes}">
        <p style="color:green; font-weight:bold; font-size:20px; text-align:center;">
            ${succes}
        </p>
    </c:if>

    <form action="CazuriController" method="POST" style="text-align:center;">

        <div style="max-height:400px; overflow-y:auto; margin-bottom:20px;">
            <table class="justice-table">
                <tr>
                    <th>
                    </th>
                    <th>ID caz</th>
                    <th>ID judecător</th>
                    <th>Nume</th>
                    <th>Prenume</th>
                    <th>CNP</th>
                    <th>Data nașterii</th>
                    <th>Grad</th>
                    <th>ID proces</th>
                    <th>Număr dosar</th>
                    <th>Tip proces</th>
                    <th>Stadiu</th>
                    <th>Data înregistrării</th>
                    <th>Denumire</th>
                </tr>

                <c:forEach var="cazuri" items="${listaCazuri}">
                    <tr>
                        <td>
                            <input type="checkbox"
                                   name="idStergere"
                                   value="${cazuri.ID_Caz}">
                        </td>
                        <td>${cazuri.ID_Caz}</td>
                        <td>${cazuri.judecatori.ID_Judecator}</td>
                        <td>${cazuri.judecatori.nume_Judecator}</td>
                        <td>${cazuri.judecatori.prenume_Judecator}</td>
                        <td>${cazuri.judecatori.CNP}</td>
                        <td>${cazuri.judecatori.data_Nasterii}</td>
                        <td>${cazuri.judecatori.grad}</td>
                        <td>${cazuri.procese.ID_Proces}</td>
                        <td>${cazuri.procese.numar_Dosar}</td>
                        <td>${cazuri.procese.tip_Proces}</td>
                        <td>${cazuri.procese.stadiu}</td>
                        <td>${cazuri.procese.data_Inregistrarii}</td>
                        <td>${cazuri.procese.denumire}</td>
                    </tr>
                </c:forEach>
            </table>
        </div>

        <label><b>ID caz</b></label>
        <select name="ID_Caz" class="justice-btn">
            <c:forEach items="${listaCazuri}" var="c">
                <option value="${c.ID_Caz}">${c.ID_Caz}</option>
            </c:forEach>
        </select>

        <label><b>ID judecător</b></label>
        <select name="ID_Judecator" class="justice-btn">
            <c:forEach items="${listaJudecatori}" var="j">
                <option value="${j.ID_Judecator}">
                    ${j.ID_Judecator} - ${j.nume_Judecator} ${j.prenume_Judecator}
                </option>
            </c:forEach>
        </select>

        <label><b>ID proces</b></label>
        <select name="ID_Proces" class="justice-btn">
            <c:forEach items="${listaProcese}" var="p">
                <option value="${p.ID_Proces}">
                    ${p.ID_Proces} - ${p.numar_Dosar}
                </option>
            </c:forEach>
        </select>

<div class="justice-actions-row">

    <button type="submit"
            name="modificaCaz"
            class="justice-btn justice-btn-inline danger"
            onclick="return confirm('Sigur modifici acest caz?');">
        ✏️ Modifică
    </button>

    <button type="submit"
            name="stergeSelectate"
            class="justice-btn justice-btn-inline danger"
            onclick="return confirm('Sigur ștergi cazurile selectate?');">
        🗑️ Șterge selecția
    </button>

    <button type="submit"
            name="stergeTot"
            class="justice-btn justice-btn-inline danger"
            onclick="return confirm('⚠️ Sigur ștergi toate cazurile?');">
        ❌ Șterge toate
    </button>

</div>

<div class="justice-actions-row">
    <button type="button"
        class="justice-btn justice-btn-inline secondary"
        onclick="location.href='CazuriController'">
    ➕ Înapoi la adaugă caz
</button>

<button type="button"
        class="justice-btn justice-btn-inline secondary"
        onclick="location.href='index.html'">
    🏠 Acasă
</button>
</div>

    </form>

</div>

</body>
</html>
