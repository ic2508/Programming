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

<div class="justice-card" style="width:520px;">

<%
    String[] s = request.getParameterValues("primarykey");

    if (s == null || s.length == 0) {
%>
        <h2 class="justice-title" style="color:#c0392b;">
            ❌ Niciun proces selectat
        </h2>

        <p>
            Selectează un proces pentru a-l putea modifica!
        </p>

        <button type="button"
        	class="justice-btn secondary"
        	onclick="history.back()">
    		⬅️ Înapoi la tabel
			</button>

<%
    } else if (s.length > 1) {
%>
        <h2 class="justice-title" style="color:#c0392b;">
            ❌ Selecție invalidă
        </h2>

        <p>
            Poți modifica <b>un singur proces</b> odată.
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
            "Procese",
            "ID_Proces",
            aux
        );
        rs.first();

        String numarDosar = rs.getString("Numar_Dosar");
        String tip = rs.getString("Tip_Proces");
        String stadiu = rs.getString("Stadiu");
        String data = rs.getString("Data_Inregistrarii");
        String denumire = rs.getString("Denumire");

        rs.close();
        jb.disconnect();
%>

        <h2 class="justice-title">⚖️ Modifică proces ⚖️</h2>

        <form action="m2_proces.jsp" method="post">

            <label>ID Proces</label>
            <input type="text" class="justice-btn"
                   name="ID_Proces"
                   value="<%= aux %>" readonly>

            <br><br>

           <label>Număr dosar</label>
				<input type="text"
       			class="justice-btn"
       			name="Numar_Dosar"
       			value="<%= numarDosar %>"
       			pattern="[0-9]{4}/[0-9]{4}"
       			title="Format obligatoriu: xxxx/xxxx"
       			required>

            <br><br>

            <label>Tip proces</label>
            <input type="text" class="justice-btn"
                   name="Tip_Proces"
                   value="<%= tip %>" required>

            <br><br>

            <label>Stadiu</label>
            <input type="text" class="justice-btn"
                   name="Stadiu"
                   value="<%= stadiu %>" required>

            <br><br>

            <label>Data înregistrării</label>
            <input type="date" class="justice-btn"
                   name="Data_Inregistrarii"
                   value="<%= data %>" required>

            <br><br>

            <label>Denumire</label>
            <input type="text" class="justice-btn"
                   name="Denumire"
                   value="<%= denumire %>" required>

            <br>

            <button type="submit" class="justice-btn success">
    			💾 Salvează modificările
			</button>

        </form>


        <div class="justice-nav-row">
            <button type="button"
        	class="justice-btn secondary"
        	onclick="history.back()">
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
