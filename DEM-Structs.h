/************************************************************************************
DEM-Solver-CPU
Dsicrete Element Method Program for landsldies, debris flows and other geohazards
--parallelized and optimized for SMP (Symmetric multiprocessing) architecture.
--optimized for AVX2 instructions.
--Copyright (c) 2018-2024, Weijie ZHANG, GeoHohai, Hohai University.
************************************************************************************/
/************************************************************************************
DEM-Structs.h: all the statements of strctures in the DEM calculations.
************************************************************************************/

#pragma once
typedef struct vec_t {
	float x = 0.0f;   //component at x coordinate
	float y = 0.0f;   //component at y coordinate
	float z = 0.0f;   //component at z coordinate
};

vec_t operator+(const vec_t& a, const vec_t& b) {
	vec_t temp;
	temp.x = a.x + b.x;
	temp.y = a.y + b.y;
	temp.z = a.z + b.z;
	return temp;
}

vec_t operator-(const vec_t& a, const vec_t& b) {
	vec_t temp;
	temp.x = a.x - b.x;
	temp.y = a.y - b.y;
	temp.z = a.z - b.z;
	return temp;
}

vec_t operator*(const vec_t& a, const vec_t& b) {
	vec_t temp;
	temp.x = a.x * b.x;
	temp.y = a.y * b.y;
	temp.z = a.z * b.z;
	return temp;
}

vec_t operator*(const vec_t& a, const float& b) {
	vec_t temp;
	temp.x = a.x * b;
	temp.y = a.y * b;
	temp.z = a.z * b;
	return temp;
}

float dot_prod(const vec_t& a, const vec_t& b) {
	return a.x * b.x + a.y * b.y + a.z * b.z;
}

typedef struct stru_pro_para {
	int ntotal = 0;     //total number of elements
	int fop = 1;        //define the steps for output
	int loop = 0;       //define the total steps for simulation
	float dt = 0.0f;    //time increament for integration
	float t = 0.0f;     //total simulation time
	int type_cont = 1;  //type of contact model: default 1.
	int type_ang = 0;   //considering angluar velocoty? 0--no, 1--yes.
	int type_damp = 0;  //considering damping effect? 0--no, 1--yes.
	int type_fail = 0;  //type of friction model: 0--Mohr-Coulomb failure criteron.
};

typedef struct stru_element_prop {
	int type = 0;    //element type: 0--fixed element; 1--flow element; 2--flexible net or wall.
	float size = 0.0f;     //size of element
	float k_n = 0.0f;      //normal stiffness
	float k_s = 0.0f;      //tangential stiffness
	float c_d = 0.0f;      //damping coefficient
	float f_c = 0.0f;      //friction coeficient
	float f_i = 0.0f;      //initial friction force
};

typedef struct stru_bound_prop {
	vec_t point;    //define a point on the plane
	vec_t vec_n;    //define the normal direction
	float D;   //parameters D for the plane equation
};

typedef struct stru_element_movement {
	vec_t posi_t;   //position at time t
	vec_t vel_t;    //velocity at time t
	vec_t vel_pre;  //velocity at previous time
	vec_t acc_t;    //acceleration at time t
	vec_t acc_pre;  //acceleration at previous time
	vec_t ang_v_t;  //angular velocity at time t
	vec_t ang_v_pre;  //angular velocity at previous time
	vec_t ang_acc_t;  //angular acceleration at time t
	vec_t ang_acc_pre;  //angular acceleration at previous time
};

typedef struct stru_element_force {
	vec_t n_f;   //normal force
	vec_t t_f;   //tangential force
	vec_t m_f;   //moment
};

typedef struct stru_grid_element {
	int e_id = -1;     //index of element
	int g_id = -1;     //index of grid
};

typedef struct stru_grid_info {
	int start = -1;  //start index of stru_grid_element
	int end = 1;     //end index of stru_grid_element
};

typedef struct stru_grid_info {
	int total = 0;       //total number of influencing elements
	int ids_e[30];   //indexes of influencing elements
};