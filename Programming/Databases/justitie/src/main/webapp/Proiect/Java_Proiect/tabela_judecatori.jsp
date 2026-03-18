<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8"%>
<%@ page language="java" import="java.lang.*,java.math.*,db.*,java.sql.*, java.io.*, java.util.*"%>

<!DOCTYPE html>
<html>
<head>
    <meta charset="UTF-8">
    <title>Tabela judecători</title>
    <link rel="stylesheet" href="css/view.css?v=123">
       <script>
document.addEventListener("DOMContentLoaded", function () {
    const selectAll = document.getElementById("selectAll");

    selectAll.addEventListener("change", function () {
        const checkboxes = document.querySelectorAll(
            'input[name="primarykey"]'
        );
        checkboxes.forEach(cb => cb.checked = this.checked);
    });
});
</script>
</head>

<jsp:useBean id="jb" scope="session" class="db.JavaBean" />
<jsp:setProperty name="jb" property="*" />

<body class="page-justice">

    <div class="justice-card" style="width: 90%; max-width: 1200px;">

        <h1 class="justice-title">👨‍⚖️ Tabela judecători</h1>


        <br>

        <form action="sterge_judecator.jsp" method="post">

            <div style="overflow-x:auto;">

                <table class="justice-table">
                    <thead>
                        <tr>
                            <th><input type="checkbox" id="selectAll"></th>
                            <th>ID Judecător</th>
                            <th>Nume</th>
                            <th>Prenume</th>
                            <th>CNP</th>
                            <th>Data nașterii</th>
                            <th>Grad</th>
                        </tr>
                    </thead>

                    <tbody>
                    <%
                        jb.connect();
                        ResultSet rs = jb.vedeTabela("Judecatori");
                        long x;

                        while (rs.next()) {
                            x = rs.getInt("ID_Judecator");
                    %>
                        <tr>
                            <td>
                                <input type="checkbox" name="primarykey" value="<%= x %>">
                            </td>
                            <td><%= x %></td>
                            <td><%= rs.getString("Nume_Judecator") %></td>
                            <td><%= rs.getString("Prenume_Judecator") %></td>
                            <td><%= rs.getString("CNP") %></td>
                            <td><%= rs.getDate("Data_Nasterii") %></td>
                            <td><%= rs.getString("Grad") %></td>
                        </tr>
                    <%
                        }
                        rs.close();
                        jb.disconnect();
                    %>
                    </tbody>
                </table>

            </div>

			
			<div class="justice-nav-row">
            <button type="button"
            class="justice-btn success"
            onclick="location.href='nou_judecator.jsp'">
        	➕ Adaugă un nou judecător
    		</button>
			
			<button type="submit" class="justice-btn danger"
			onclick="return confirm('Sigur ștergi cazurile selectate?');">
    			🗑️ Șterge liniile marcate
			</button>
			
    		<button type="button"
            class="justice-btn secondary"
            onclick="location.href='index.html'">
        	🏠 Acasă
    		</button>
        </div>
            
			
        </form>

    </div>

</body>
</html>
