<%@page import="DAOImpl.JudecatoriDaoImpl"%>
<%@page import="pojo.Judecatori"%>
<%@page import="java.util.List"%>
<%@ taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core"%>
<%@page contentType="text/html" pageEncoding="UTF-8"%>

<%
    JudecatoriDaoImpl judecatorDaoImpl = new JudecatoriDaoImpl();
    List<Judecatori> listaJudecatori = judecatorDaoImpl.afiseazaJudecatori();
    request.setAttribute("listaJudecatori", listaJudecatori);
%>

<!DOCTYPE html>
<html lang="ro">
<head>
    <meta charset="UTF-8">
    <title>Tabela judecători</title>
    <link rel="stylesheet" href="css/style.css?v=1">

    <script src="https://ajax.googleapis.com/ajax/libs/jquery/1.12.4/jquery.min.js"></script>

    <script>
        $(function () {
            $("#selectAll").on("change", function () {
                $("input[name='idStergere']").prop("checked", this.checked);
            });
        });
    </script>
</head>

<body class="page-justice">

<div class="justice-card" style="width:90%; max-width:1100px;">

    <h1 class="justice-title">👨‍⚖️ Tabela judecători</h1>

    <c:if test="${not empty eroare}">
        <p style="color:red; font-weight:bold; font-size:18px;">
            ${eroare}
        </p>
    </c:if>

    <c:if test="${not empty succes}">
        <p style="color:green; font-weight:bold; font-size:20px;">
            ${succes}
        </p>
    </c:if>

    <form action="JudecatoriController" method="POST">

        <div style="max-height:400px; overflow-y:auto; margin-bottom:25px;">
            <table class="justice-table">
                <tr>
                    <th>
                    </th>
                    <th>ID</th>
                    <th>Nume</th>
                    <th>Prenume</th>
                    <th>CNP</th>
                    <th>Data nașterii</th>
                    <th>Grad</th>
                </tr>

                <c:forEach var="j" items="${listaJudecatori}">
                    <tr>
                        <td>
                            <input type="checkbox"
                                   name="idStergere"
                                   value="${j.ID_Judecator}">
                        </td>
                        <td>${j.ID_Judecator}</td>
                        <td>${j.nume_Judecator}</td>
                        <td>${j.prenume_Judecator}</td>
                        <td>${j.CNP}</td>
                        <td>${j.data_Nasterii}</td>
                        <td>${j.grad}</td>
                    </tr>
                </c:forEach>
            </table>
        </div>

        <label><b>ID judecător</b></label>
        <select name="ID_Judecator" class="justice-btn">
            <c:forEach items="${listaJudecatori}" var="j">
                <option value="${j.ID_Judecator}">
                    ${j.ID_Judecator}
                </option>
            </c:forEach>
        </select>

        <label><b>Nume</b></label>
        <input type="text" name="Nume_Judecator" class="justice-btn">

        <label><b>Prenume</b></label>
        <input type="text" name="Prenume_Judecator" class="justice-btn">

        <label><b>CNP</b></label>
        <input type="text" name="CNP" class="justice-btn">

        <label><b>Data nașterii</b></label>
        <input type="date" name="Data_Nasterii" class="justice-btn">

        <label><b>Grad</b></label>
        <input type="text" name="Grad" class="justice-btn">

        <div class="justice-actions-row">

            <button type="submit"
                    name="modificaJudecator"
                    class="justice-btn justice-btn-inline danger"
                    onclick="return confirm('Sigur modifici acest judecător?');">
                ✏️ Modifică
            </button>

            <button type="submit"
                    name="stergeJudecatoriSelectati"
                    class="justice-btn justice-btn-inline danger"
                    onclick="return confirm('Sigur ștergi judecătorii selectați?');">
                🗑️ Șterge selecția
            </button>

            <button type="submit"
                    name="stergeTotiJudecatorii"
                    class="justice-btn justice-btn-inline danger"
                    onclick="return confirm('⚠️ Sigur ștergi TOȚI judecătorii?');">
                ❌ Șterge toate
            </button>

        </div>

        <div class="justice-actions-row">
                <button type="button"
        			class="justice-btn justice-btn-inline secondary"
        			onclick="location.href='adauga_judecator.jsp'">
    				➕ Înapoi la adaugă judecător
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
