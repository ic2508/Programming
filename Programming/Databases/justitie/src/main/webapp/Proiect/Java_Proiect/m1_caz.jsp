<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8"%>
<%@ page language="java" import="db.*,java.sql.*"%>

<!DOCTYPE html>
<html>
<head>
    <meta charset="UTF-8">
    <title>Modificare caz</title>
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
            ❌ Niciun caz selectat
        </h2>

        <p>
            Selectează un caz pentru a-l putea modifica!
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
            Poți modifica <b>un singur caz</b> odată.
        </p>

        <button type="button"
        	class="justice-btn secondary"
        	onclick="history.back()">
    		⬅️ Înapoi la tabel
			</button>

<%
    } else {
        int idCaz = Integer.parseInt(s[0]);

        jb.connect();
        ResultSet rs = jb.intoarceCazId(idCaz);
        rs.first();

        int idJud = rs.getInt("ID_Judecator");
        int idProc = rs.getInt("ID_Proces");

        ResultSet rsJud = jb.vedeTabela("Judecatori");
        ResultSet rsProc = jb.vedeTabela("Procese");
%>

        <h2 class="justice-title">⚖️ Modifică caz ⚖️</h2>

        <form action="m2_caz.jsp" method="post">

            <input type="hidden" name="ID_Caz" value="<%= idCaz %>">

            <label><b>Judecător</b></label>
            <select name="ID_Judecator" class="justice-btn" required>
                <%
                    while (rsJud.next()) {
                        int id = rsJud.getInt("ID_Judecator");
                %>
                    <option value="<%= id %>"
                        <%= (id == idJud ? "selected" : "") %>>
                        <%= id %> –
                        <%= rsJud.getString("Nume_Judecator") %>
                        <%= rsJud.getString("Prenume_Judecator") %>
                    </option>
                <%
                    }
                %>
            </select>

            <br><br>

            <label><b>Proces</b></label>
            <select name="ID_Proces" class="justice-btn" required>
                <%
                    while (rsProc.next()) {
                        int id = rsProc.getInt("ID_Proces");
                %>
                    <option value="<%= id %>"
                        <%= (id == idProc ? "selected" : "") %>>
                        <%= id %> –
                        <%= rsProc.getString("Numar_Dosar") %>
                    </option>
                <%
                    }
                %>
            </select>

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
        rs.close();
        rsJud.close();
        rsProc.close();
        jb.disconnect();
    }
%>

</div>

</body>
</html>
