<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8"%>
<%@ page language="java" import="db.*,java.sql.*"%>

<!DOCTYPE html>
<html>
<head>
    <meta charset="UTF-8">
    <title>Modificare proces</title>
    <link rel="stylesheet" href="css/view.css?v=123">
</head>

<jsp:useBean id="jb" scope="session" class="db.JavaBean" />

<body class="page-justice">

<div class="justice-card" style="width:480px;">

<%
    String sId = request.getParameter("ID_Proces");
    String numar = request.getParameter("Numar_Dosar");
    String tip = request.getParameter("Tip_Proces");
    String stadiu = request.getParameter("Stadiu");
    String data = request.getParameter("Data_Inregistrarii");
    String denumire = request.getParameter("Denumire");

    if (sId == null || numar == null) {
        response.sendRedirect("modifica_proces.jsp");
        return;
    }

    int idProces = Integer.parseInt(sId);

    jb.connect();

    try {

        if (jb.existaProcesLaModificare(idProces, numar)) {
%>
            <h2 class="justice-title" style="color:#c0392b;">
                ❌ Modificare invalidă
            </h2>

            <p>
                Există deja un alt proces cu acest număr de dosar!
            </p>

            <button type="button"
        	class="justice-btn secondary"
        	onclick="history.back()">
    		⬅️ Înapoi la tabel
			</button>
<%
        } else {
            String[] valori = {
                numar,
                tip,
                stadiu,
                data,
                denumire
            };
            String[] campuri = {
                "Numar_Dosar",
                "Tip_Proces",
                "Stadiu",
                "Data_Inregistrarii",
                "Denumire"
            };

            jb.modificaTabela("Procese", "ID_Proces", idProces, campuri, valori);
%>
            <h2 class="justice-title" style="color:#27ae60;">
                ✅ Modificare reușită
            </h2>

            <p>
                Procesul a fost modificat cu succes!
            </p>

            <button type="button"
        	class="justice-btn secondary"
        	onclick="history.back()">
    		⬅️ Înapoi la tabel
			</button>
<%
        }
    } catch (SQLException e) {
%>
        <h2 class="justice-title" style="color:#c0392b;">
            ❌ Eroare
        </h2>

        <p>
            A apărut o eroare la modificarea procesului!
        </p>

        <button type="button"
        	class="justice-btn secondary"
        	onclick="history.back()">
    		⬅️ Înapoi la tabel
			</button>
<%
    }

    jb.disconnect();
%>

</div>

</body>
</html>
