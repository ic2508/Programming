<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8"%>
<%@ page language="java" import="db.*,java.sql.*"%>

<!DOCTYPE html>
<html>
<head>
    <meta charset="UTF-8">
    <title>Modificare judecător</title>
    <link rel="stylesheet" href="css/view.css?v=123">
</head>

<jsp:useBean id="jb" scope="session" class="db.JavaBean" />

<body class="page-justice">

<div class="justice-card" style="width:480px;">

<%
    String sId = request.getParameter("ID_Judecator");
    String nume = request.getParameter("Nume_Judecator");
    String prenume = request.getParameter("Prenume_Judecator");
    String cnp = request.getParameter("CNP");
    String data = request.getParameter("Data_Nasterii");
    String grad = request.getParameter("Grad");

    if (sId == null || nume == null || prenume == null || cnp == null) {
        response.sendRedirect("modifica_judecator.jsp");
        return;
    }

    int idJud = Integer.parseInt(sId);

    jb.connect();

    try {
        if (jb.existaCNPLaModificare(idJud, cnp)) {
%>
            <h2 class="justice-title" style="color:#c0392b;">
                ❌ Modificare invalidă
            </h2>

            <p>
                Există deja un alt judecător cu acest CNP!
            </p>

            <button type="button"
        	class="justice-btn secondary"
        	onclick="history.back()">
    		⬅️ Înapoi la tabel
			</button>
<%
        } else {
            String[] valori = {
                nume,
                prenume,
                cnp,
                data,
                grad
            };
            String[] campuri = {
                "Nume_Judecator",
                "Prenume_Judecator",
                "CNP",
                "Data_Nasterii",
                "Grad"
            };

            jb.modificaTabela("Judecatori", "ID_Judecator", idJud, campuri, valori);
%>
            <h2 class="justice-title" style="color:#27ae60;">
                ✅ Modificare reușită
            </h2>

            <p>
                Judecătorul a fost modificat cu succes!
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
            A apărut o eroare la modificarea judecătorului!
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
