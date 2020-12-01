#pragma once
#include "CL_CAD.h"
#include "CL_map_TBPERSONNE.h"

namespace NS_Svc {

	ref class CL_svc_gestionPersonnes
	{
	private:
		NS_Composants::CL_CAD^ cad;
		NS_Composants::CL_map_TBPERSONNE^ personne;
		DataSet^ ds;
	public:
		CL_svc_gestionPersonnes(void);
		DataSet^ listePersonnel(String^);
		int ajouter(String^, String^);
		void modifier(int, String^, String^);
		void supprimer(int);
	};

}