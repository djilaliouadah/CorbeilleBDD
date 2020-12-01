#include "pch.h"
#include "CL_CAD.h"
#include <iostream>

namespace NS_Composants {

	void CL_CAD::setSQL(String^ rq_sql)
	{
		if (rq_sql == "" || rq_sql == "RIEN") {
			this->rq_sql = "RIEN";
		}
		else {
			this->rq_sql = rq_sql;
		}
	}

	CL_CAD::CL_CAD(void)
	{
		this->rq_sql = "RIEN";
		this->cnx = "Data Source=.;Initial Catalog=Corbeille;Integrated Security=True";
		this->CNX = gcnew SqlConnection(this->cnx);
		this->CMD = gcnew SqlCommand(this->rq_sql, this->CNX);
		//sp�cifie la facon dont une chaine de commande est interpr�t�e
		this->CMD->CommandType = CommandType::Text;
	}

	int CL_CAD::actionRowsID(String^ rq_sql)
	{
		int id;
		this->setSQL(rq_sql);
		this->CMD->CommandText = this->rq_sql;
		this->CNX->Open();
		//convertir la valeur d'un objet en un entier sign� 30 bits
		//ex�cute la requ�te et retourne la premi�re colonne de la premi�re ligne
		//du jeu de r�sultat retourn� par la requ�te
		
		id = Convert::ToInt32(this->CMD->ExecuteScalar());   //objet DBNull
		this->CNX->Close();
		return id;
	}

	void CL_CAD::actionRows(String^ rq_sql)
	{
		this->setSQL(rq_sql);
		this->CMD->CommandText = this->rq_sql;
		this->CNX->Open();
		//ex�cute la transaction SQL et retourne le nombre de lignes concern�ss
		this->CMD->ExecuteNonQuery();
		this->CNX->Close();
	}

	DataSet^ CL_CAD::getRows(String^ rq_sql, String^ dataTableName)
	{
		this->setSQL(rq_sql);
		//encemble de commandes BDD pour remplir le DataSet
		this->DA = gcnew SqlDataAdapter(this->CMD);
		this->CMD->CommandText = this->rq_sql;
		this->DS = gcnew DataSet();
		this->DA->Fill(this->DS, dataTableName);
		return this->DS;
	}

}