<%@page import="DAOImpl.ProceseDaoImpl"%>
<%@page import="pojo.Procese"%>
<%@page import="java.util.List"%>
<%@ taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core"%>
<%@page contentType="text/html" pageEncoding="UTF-8"%>

<%
    ProceseDaoImpl procesDaoImpl = new ProceseDaoImpl();
    List<Procese> listaProcese = procesDaoImpl.afiseazaProcese();
    request.setAttribute("listaProcese", listaProcese);
%>

<!DOCTYPE html>
<html lang="ro">
<head>
    <meta charset="UTF-8">
    <title>Tabela procese</title>

    <link rel="stylesheet" href="css/style.css?v=123">

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

    <h1 class="justice-title">📜 Tabela procese</h1>

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

    <form action="ProceseController" method="POST">

        <div style="max-height:400px; overflow-y:auto; margin-bottom:25px;">
            <table class="justice-table">
                <tr>
                    <th>
                    </th>
                    <th>ID</th>
                    <th>Număr dosar</th>
                    <th>Tip proces</th>
                    <th>Stadiu</th>
                    <th>Data înregistrării</th>
                    <th>Denumire</th>
                </tr>

                <c:forEach var="p" items="${listaProcese}">
                    <tr>
                        <td>
                            <input type="checkbox"
                                   name="idStergere"
                                   value="${p.ID_Proces}">
                        </td>
                        <td>${p.ID_Proces}</td>
                        <td>${p.numar_Dosar}</td>
                        <td>${p.tip_Proces}</td>
                        <td>${p.stadiu}</td>
                        <td>${p.data_Inregistrarii}</td>
                        <td>${p.denumire}</td>
                    </tr>
                </c:forEach>
            </table>
        </div>

        <label><b>ID proces</b></label>
        <select name="ID_Proces" class="justice-btn">
            <c:forEach items="${listaProcese}" var="p">
                <option value="${p.ID_Proces}">
                    ${p.ID_Proces}
                </option>
            </c:forEach>
        </select>

        <label><b>Număr dosar</b></label>
        <input type="text" name="Numar_Dosar" class="justice-btn">

        <label><b>Tip proces</b></label>
        <input type="text" name="Tip_Proces" class="justice-btn">

        <label><b>Stadiu</b></label>
        <input type="text" name="Stadiu" class="justice-btn">

        <label><b>Data înregistrării</b></label>
        <input type="date" name="Data_Inregistrarii" class="justice-btn">

        <label><b>Denumire</b></label>
        <input type="text" name="Denumire" class="justice-btn">

        <div class="justice-actions-row">

            <button type="submit"
                    name="modificaProces"
                    class="justice-btn justice-btn-inline danger"
                    onclick="return confirm('Sigur modifici acest proces?');">
                ✏️ Modifică
            </button>

            <button type="submit"
                    name="stergeProceseSelectate"
                    class="justice-btn justice-btn-inline danger"
                    onclick="return confirm('Sigur ștergi procesele selectate?');">
                🗑️ Șterge selecția
            </button>

            <button type="submit"
                    name="stergeToateProcesele"
                    class="justice-btn justice-btn-inline danger"
                    onclick="return confirm('⚠️ Sigur ștergi TOATE procesele?');">
                ❌ Șterge toate
            </button>

        </div>

        <div class="justice-nav-row">
            <button type="button"
        			class="justice-btn justice-btn-inline secondary"
        			onclick="location.href='adauga_proces.jsp'">
    				➕ Înapoi la adaugă proces
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
