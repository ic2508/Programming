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
    String[] s = request.getParameterValues("primarykey");

    if (s == null || s.length == 0) {
%>
        <h2 class="justice-title" style="color:#c0392b;">
            ❌ Niciun judecător selectat
        </h2>

        <p>
            Selectează un judecător pentru a-l putea modifica!
        </p>

        <button type="button"
        	class="justice-btn secondary"
        	onclick="history.back()">
    		⬅️ Înapoi la tabel
			</button>

<%
    /* ❌ mai multe selectate */
    } else if (s.length > 1) {
%>
        <h2 class="justice-title" style="color:#c0392b;">
            ❌ Selecție invalidă
        </h2>

        <p>
            Poți modifica <b>un singur judecător</b> odată.
        </p>

        <button type="button"
        	class="justice-btn secondary"
        	onclick="history.back()">
    		⬅️ Înapoi la tabel
			</button>

<%
    } else {
        int aux = Integer.parseInt(s[0]);

        jb.connect();
        ResultSet rs = jb.intoarceLinieDupaId(
            "Judecatori",
            "ID_Judecator",
            aux
        );
        rs.first();

        String nume = rs.getString("Nume_Judecator");
        String prenume = rs.getString("Prenume_Judecator");
        String cnp = rs.getString("CNP");
        String data = rs.getString("Data_Nasterii");
        String grad = rs.getString("Grad");

        rs.close();
        jb.disconnect();
%>

        <h2 class="justice-title">⚖️ Modifică judecător ⚖️</h2>

        <form action="m2_judecator.jsp" method="post">

            <label>ID Judecător</label>
            <input type="text" class="justice-btn"
                   name="ID_Judecator"
                   value="<%= aux %>" readonly>

            <br><br>

            <label>Nume</label>
            <input type="text" class="justice-btn"
                   name="Nume_Judecator"
                   value="<%= nume %>" required>

            <br><br>

            <label>Prenume</label>
            <input type="text" class="justice-btn"
                   name="Prenume_Judecator"
                   value="<%= prenume %>" required>

            <br><br>

            <label>CNP</label>
            <input type="text" class="justice-btn"
                   name="CNP"
                   value="<%= cnp %>"
                   pattern="[0-9]{13}"
                   title="CNP trebuie să aibă 13 cifre"
                   required>

            <br><br>

            <label>Data nașterii</label>
            <input type="date" class="justice-btn"
                   name="Data_Nasterii"
                   value="<%= data %>" required>

            <br><br>

            <label>Grad</label>
            <input type="text" class="justice-btn"
                   name="Grad"
                   value="<%= grad %>" required>

            <br>

            <button type="submit" class="justice-btn success">
    			💾 Salvează modificările
			</button>

        </form>

        

    	<div class="justice-nav-row">
            <button type="button"
            class="justice-btn secondary"
            onclick="location.href='modifica_judecator.jsp'">
        	⬅️ Înapoi la tabel
    	</button>

    		<button type="button"
            class="justice-btn secondary"
            onclick="location.href='index.html'">
        	🏠 Acasă
    		</button>
        </div>

<%
    }
%>

</div>

</body>
</html>
