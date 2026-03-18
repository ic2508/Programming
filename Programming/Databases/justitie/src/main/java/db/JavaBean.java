package db; 
import java.sql.*; 

public class JavaBean { 
	String error; 
	Connection con; 
	public JavaBean() { 
	} 
	public void connect() throws ClassNotFoundException, SQLException, Exception { 
		try { 
			Class.forName("com.mysql.cj.jdbc.Driver"); 
			con = DriverManager.getConnection("jdbc:mysql://localhost:3306/justitie?useSSL=false","root", "root123GG$69"); 
		} catch (ClassNotFoundException cnfe) { 
			error = "ClassNotFoundException: Nu s-a gasit driverul bazei de date."; 
			throw new ClassNotFoundException(error); 
		} catch (SQLException cnfe) { 
			error = "SQLException: Nu se poate conecta la baza de date."; 
			throw new SQLException(error); 
		} catch (Exception e) { 
			error = "Exception: A aparut o exceptie neprevazuta in timp ce se stabilea legatura la baza de date."; 
					throw new Exception(error); 
		} 
	}

	public void connect(String bd) throws ClassNotFoundException, SQLException, Exception { 
		try { 
			Class.forName("com.mysql.cj.jdbc.Driver"); 
			con = DriverManager.getConnection("jdbc:mysql://localhost:3306/" + bd, "root", "root123GG$69"); 
		} catch (ClassNotFoundException cnfe) { 
			error = "ClassNotFoundException: Nu s-a gasit driverul bazei de date."; 
			throw new ClassNotFoundException(error); 
		} catch (SQLException cnfe) { 
			error = "SQLException: Nu se poate conecta la baza de date."; 
			throw new SQLException(error); 
		} catch (Exception e) { 
			error = "Exception: A aparut o exceptie neprevazuta in timp ce se stabilea legatura la baza de date."; 
					throw new Exception(error); 
		} 
	}

	public void connect(String bd, String ip) throws ClassNotFoundException, SQLException, 
	Exception { 
		try { 
			Class.forName("com.mysql.cj.jdbc.Driver"); 
			con = DriverManager.getConnection("jdbc:mysql://" + ip + ":3306/" + bd, "root", "root123GG$69"); 
		} catch (ClassNotFoundException cnfe) { 
			error = "ClassNotFoundException: Nu s-a gasit driverul bazei de date."; 
			throw new ClassNotFoundException(error); 
		} catch (SQLException cnfe) { 
			error = "SQLException: Nu se poate conecta la baza de date."; 
			throw new SQLException(error); 



		} catch (Exception e) { 
			error = "Exception: A aparut o exceptie neprevazuta in timp ce se stabilea legatura la baza de date."; 
					throw new Exception(error); 
		} 
	}

	public void disconnect() throws SQLException { 
		try { 
			if (con != null) { 
				con.close(); 
			} 
		} catch (SQLException sqle) { 
			error = ("SQLException: Nu se poate inchide conexiunea la baza de date."); 
			throw new SQLException(error); 
		} 
	}

	public void adaugaJudecator(String Nume_Judecator, String Prenume_Judecator, String CNP, String Data_Nasterii, String Grad) 
			throws SQLException, Exception { 
		if (con != null) { 
			try { 
				Statement stmt; 
				stmt = con.createStatement(); 
				stmt.executeUpdate("insert into Judecatori(Nume_Judecator, Prenume_Judecator, CNP, Data_Nasterii, Grad) values('" + Nume_Judecator 
						+ "'  , '" + Prenume_Judecator + "', '" + CNP + "', '" + Data_Nasterii + "', '" + Grad + "');"); 

			} catch (SQLException sqle) { 
				error = "ExceptieSQL: Reactualizare nereusita; este posibil sa existe duplicate."; 
				throw new SQLException(error); 
			} 
		} else { 
			error = "Exceptie: Conexiunea cu baza de date a fost pierduta."; 
			throw new Exception(error); 
		} 
	}

	public void adaugaProces(String Numar_Dosar, String Tip_Proces, String Stadiu, String Data_Inregistrarii, String Denumire) 
			throws SQLException, Exception { 
		if (con != null) { 
			try { 
				Statement stmt; 
				stmt = con.createStatement(); 
				stmt.executeUpdate(
					    "INSERT INTO Procese (Numar_Dosar, Tip_Proces, Stadiu, Data_Inregistrarii, Denumire) " +
					    "VALUES ('" + Numar_Dosar + "', '" + Tip_Proces + "', '" + Stadiu + "', '" + Data_Inregistrarii + "', '" + Denumire + "');"
					);

			} catch (SQLException sqle) { 
				error = "ExceptieSQL: Reactualizare nereusita; este posibil sa existe duplicate."; 
				throw new SQLException(error); 
			} 
		} else { 
			error = "Exceptie: Conexiunea cu baza de date a fost pierduta."; 
			throw new Exception(error); 
		} 
	}

	public void adaugaCaz(int ID_Judecator, int ID_Proces) 
					throws SQLException, Exception { 
		if (con != null) { 
			try { 
				Statement stmt; 
				stmt = con.createStatement(); 
				stmt.executeUpdate("insert into Cazuri(ID_Judecator, ID_Proces) values('" + ID_Judecator + "'  , '" + ID_Proces + "');"); 

			} catch (SQLException sqle) { 
				error = "ExceptieSQL: Reactualizare nereusita; este posibil sa existe duplicate."; 
				throw new SQLException(error); 
			} 
		} else { 
			error = "Exceptie: Conexiunea cu baza de date a fost pierduta."; 
			throw new Exception(error); 
		} 
	}

	public ResultSet vedeTabela(String tabel) throws SQLException, Exception { 
		ResultSet rs = null; 
		try { 
			String queryString = ("select * from `justitie`.`" + tabel + "`;"); 



			Statement stmt = con.createStatement(/*ResultSet.TYPE_SCROLL_INSENSITIVE, 
ResultSet.CONCUR_READ_ONLY*/); 
			rs = stmt.executeQuery(queryString); 
		} catch (SQLException sqle) { 
			error = "SQLException: Interogarea nu a fost posibila."; 
			throw new SQLException(error); 
		} catch (Exception e) { 
			error = "A aparut o exceptie in timp ce se extrageau datele."; 
			throw new Exception(error); 
		} 
		return rs; 
	}

	public ResultSet vedeCaz() throws SQLException, Exception { 
	    ResultSet rs = null; 
	    try { 
	        String queryString = 
	            "SELECT a.Nume_Judecator, a.Prenume_Judecator, a.CNP, a.Data_Nasterii, a.Grad, " +
	            "b.Numar_Dosar, b.Tip_Proces, b.Stadiu, b.Data_Inregistrarii, b.Denumire, " +
	            "c.ID_Caz, c.ID_Proces, c.ID_Judecator " +
	            "FROM Judecatori a, Procese b, Cazuri c " +
	            "WHERE a.ID_Judecator = c.ID_Judecator " +
	            "AND b.ID_Proces = c.ID_Proces " +
	            "ORDER BY c.ID_Caz ASC";

	        Statement stmt = con.createStatement();
	        rs = stmt.executeQuery(queryString); 

	    } catch (SQLException sqle) { 
	        error = "SQLException: Interogarea nu a fost posibila."; 
	        throw new SQLException(error); 
	    } catch (Exception e) { 
	        error = "A aparut o exceptie in timp ce se extrageau datele."; 
	        throw new Exception(error); 
	    } 
	    return rs; 
	}

	public void stergeDateTabela(String[] primaryKeys, String tabela, String dupaID) throws 
	SQLException, Exception { 
		if (con != null) { 
			try { 
				long aux; 
				PreparedStatement delete; 
				delete = con.prepareStatement("DELETE FROM " + tabela + " WHERE " + dupaID + "=?;"); 
				for (int i = 0; i < primaryKeys.length; i++) { 
					aux = java.lang.Long.parseLong(primaryKeys[i]); 
					delete.setLong(1, aux); 
					delete.execute(); 
				} 
			} catch (SQLException sqle) { 
				error = "ExceptieSQL: Reactualizare nereusita; este posibil sa existe duplicate."; 
				throw new SQLException(error); 
			} catch (Exception e) { 
				error = "A aparut o exceptie in timp ce erau sterse inregistrarile."; 
				throw new Exception(error); 
			} 
		} else { 
			error = "Exceptie: Conexiunea cu baza de date a fost pierduta."; 
			throw new Exception(error); 
		} 
	}

	public void stergeTabela(String tabela) throws SQLException, Exception { 
		if (con != null) { 
			try { 
				Statement stmt; 
				stmt = con.createStatement(); 
				stmt.executeUpdate("delete from " + tabela + ";"); 
			} catch (SQLException sqle) { 
				error = "ExceptieSQL: Stergere nereusita; este posibil sa existe duplicate."; 
				throw new SQLException(error); 
			} 
		} else { 
			error = "Exceptie: Conexiunea cu baza de date a fost pierduta."; 
			throw new Exception(error); 
		} 
	}

	public void modificaTabela(String tabela, String IDTabela, int ID, String[] campuri, String[] 
			valori) throws SQLException, Exception { 
		String update = "update " + tabela + " set "; 
		String temp = ""; 
		if (con != null) { 
			try { 
				for (int i = 0; i < campuri.length; i++) { 
					if (i != (campuri.length - 1)) { 
						temp = temp + campuri[i] + "='" + valori[i] + "', "; 
					} else { 
						temp = temp + campuri[i] + "='" + valori[i] + "' where " + IDTabela + " = '" + ID + "';"; 



					} 
				} 
				update = update + temp; 
				Statement stmt; 
				stmt = con.createStatement(); 
				stmt.executeUpdate(update); 
			} catch (SQLException sqle) { 
				error = "ExceptieSQL: Reactualizare nereusita; este posibil sa existe duplicate."; 
				throw new SQLException(error); 
			} 
		} else { 
			error = "Exceptie: Conexiunea cu baza de date a fost pierduta."; 
			throw new Exception(error); 
		} 
	}

	public ResultSet intoarceLinie(String tabela, int ID) throws SQLException, Exception { 
		ResultSet rs = null; 
		try { 
			String queryString = ("SELECT * FROM " + tabela + " where ID_Judecator=" + ID + ";"); 
			Statement stmt = con.createStatement(ResultSet.TYPE_SCROLL_INSENSITIVE, 
					ResultSet.CONCUR_READ_ONLY); 
			rs = stmt.executeQuery(queryString); //sql exception 
		} catch (SQLException sqle) { 
			error = "SQLException: Interogarea nu a fost posibila."; 
			throw new SQLException(error); 
		} catch (Exception e) { 
			error = "A aparut o exceptie in timp ce se extrageau datele."; 
			throw new Exception(error); 
		} 
		return rs; 
	}

	public ResultSet intoarceLinieDupaId(String tabela, String denumireId, int ID) throws 
	SQLException, Exception { 
		ResultSet rs = null; 
		try { 
			String queryString = ("SELECT * FROM " + tabela + " where " + denumireId + "=" + ID 
					+ ";"); 
			Statement stmt = con.createStatement(ResultSet.TYPE_SCROLL_INSENSITIVE, 
					ResultSet.CONCUR_READ_ONLY); 
			rs = stmt.executeQuery(queryString);
		} catch (SQLException sqle) { 
			error = "SQLException: Interogarea nu a fost posibila."; 
			throw new SQLException(error); 
		} catch (Exception e) { 
			error = "A aparut o exceptie in timp ce se extrageau datele."; 
			throw new Exception(error); 
		} 
		return rs; 
	}
	public ResultSet intoarceCazId(int ID) throws SQLException, Exception { 
		ResultSet rs = null; 
		try { 
			String queryString = ("select a.Nume_Judecator, a.Prenume_Judecator, a.CNP, a.Data_Nasterii, a.Grad, b.Numar_Dosar , b.Tip_Proces, b.Stadiu, b.Data_Inregistrarii, b.Denumire, c.ID_Caz, c.ID_Proces , c.ID_Judecator  from Judecatori a, Procese b, Cazuri c where a.ID_Judecator = c.ID_Judecator and b.ID_Proces = c.ID_Proces and ID_Caz = '" + ID + "';"); 
			Statement stmt = con.createStatement(ResultSet.TYPE_SCROLL_INSENSITIVE, 
					ResultSet.CONCUR_READ_ONLY); 
			rs = stmt.executeQuery(queryString);
		} catch (SQLException sqle) { 
			error = "SQLException: Interogarea nu a fost posibila."; 
			throw new SQLException(error); 
		} catch (Exception e) { 
			error = "A aparut o exceptie in timp ce se extrageau datele."; 
			throw new Exception(error); 
		} 
		return rs; 
	}
	
	public boolean existaCaz(int idJudecator, int idProces) throws SQLException {
	    String sql = "SELECT COUNT(*) FROM Cazuri WHERE ID_Judecator=? AND ID_Proces=?";
	    PreparedStatement ps = con.prepareStatement(sql);
	    ps.setInt(1, idJudecator);
	    ps.setInt(2, idProces);

	    ResultSet rs = ps.executeQuery();
	    rs.next();
	    return rs.getInt(1) > 0;
	}
	
	public boolean existaCNP(String cnp) throws SQLException {
	    String sql = "SELECT COUNT(*) FROM Judecatori WHERE CNP = ?";
	    PreparedStatement ps = con.prepareStatement(sql);
	    ps.setString(1, cnp);

	    ResultSet rs = ps.executeQuery();
	    rs.next();
	    return rs.getInt(1) > 0;
	}
	
	public boolean existaProces(String numarDosar) throws SQLException {
	    String sql = "SELECT COUNT(*) FROM Procese WHERE Numar_Dosar = ?";
	    PreparedStatement ps = con.prepareStatement(sql);
	    ps.setString(1, numarDosar);

	    ResultSet rs = ps.executeQuery();
	    rs.next();
	    return rs.getInt(1) > 0;
	}
	
	public boolean existaCazLaModificare(int idCaz, int idJudecator, int idProces) throws SQLException {
	    String sql = """
	        SELECT COUNT(*) 
	        FROM Cazuri 
	        WHERE ID_Judecator = ? 
	          AND ID_Proces = ?
	          AND ID_Caz <> ?
	    """;

	    PreparedStatement ps = con.prepareStatement(sql);
	    ps.setInt(1, idJudecator);
	    ps.setInt(2, idProces);
	    ps.setInt(3, idCaz);

	    ResultSet rs = ps.executeQuery();
	    rs.next();
	    return rs.getInt(1) > 0;
	}
	
	public boolean existaCNPLaModificare(int idJudecator, String cnp) throws SQLException {
	    String sql = """
	        SELECT COUNT(*) 
	        FROM Judecatori 
	        WHERE CNP = ?
	          AND ID_Judecator <> ?
	    """;

	    PreparedStatement ps = con.prepareStatement(sql);
	    ps.setString(1, cnp);
	    ps.setInt(2, idJudecator);

	    ResultSet rs = ps.executeQuery();
	    rs.next();
	    return rs.getInt(1) > 0;
	}
	
	public boolean existaProcesLaModificare(int idProces, String numarDosar) throws SQLException {
	    String sql = """
	        SELECT COUNT(*) 
	        FROM Procese 
	        WHERE Numar_Dosar = ?
	          AND ID_Proces <> ?
	    """;

	    PreparedStatement ps = con.prepareStatement(sql);
	    ps.setString(1, numarDosar);
	    ps.setInt(2, idProces);

	    ResultSet rs = ps.executeQuery();
	    rs.next();
	    return rs.getInt(1) > 0;
	}


} 