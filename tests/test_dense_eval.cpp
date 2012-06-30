/**
 * @file test_dense_eval.cpp
 *
 * Unit test of evaluation of dense matrices
 *
 * @author Dahua Lin
 */


#include "test_base.h"
#include <light_mat/matrix/matrix_classes.h>

using namespace lmat;
using namespace lmat::test;

template<class Arr>
void fill_lin(IArray<Arr, double>& arr)
{
	for (index_t i = 0; i < arr.nelems(); ++i)
		arr[i] = double(i + 1);
}

MN_CASE( mat_eval, dense_mat )
{
	const index_t m = M == 0 ? 4 : M;
	const index_t n = N == 0 ? 5 : N;

	scoped_array<double> s(m * n);
	fill_lin(s);

	dense_matrix<double, M, N> a(m, n, copy_from(s.ptr_begin()));
	dense_matrix<double, M, N> r = eval(a);

	ASSERT_EQ( r.nrows(), m );
	ASSERT_EQ( r.ncolumns(), n );
	ASSERT_NE( r.ptr_data(), a.ptr_data() );

	ASSERT_MAT_EQ(m, n, a, r);
}

MN_CASE( mat_eval, ref_mat )
{
	const index_t m = M == 0 ? 4 : M;
	const index_t n = N == 0 ? 5 : N;

	scoped_array<double> s(m * n);
	fill_lin(s);

	ref_matrix<double, M, N> a(s.ptr_begin(), m, n);
	dense_matrix<double, M, N> r = eval(a);

	ASSERT_EQ( r.nrows(), m );
	ASSERT_EQ( r.ncolumns(), n );
	ASSERT_NE( r.ptr_data(), a.ptr_data() );

	ASSERT_MAT_EQ(m, n, a, r);
}


MN_CASE( mat_eval, ref_mat_ex )
{
	const index_t ldim = 7;
	const index_t m = M == 0 ? 4 : M;
	const index_t n = N == 0 ? 5 : N;

	scoped_array<double> s(ldim * n);
	fill_lin(s);

	ref_matrix_ex<double, M, N> a(s.ptr_begin(), m, n, ldim);
	dense_matrix<double, M, N> r = eval(a);

	ASSERT_EQ( r.nrows(), m );
	ASSERT_EQ( r.ncolumns(), n );
	ASSERT_NE( r.ptr_data(), a.ptr_data() );

	ASSERT_MAT_EQ(m, n, a, r);
}


BEGIN_TPACK( dense_mat_eval )
	ADD_MN_CASE( mat_eval, dense_mat, 0, 0 );
	ADD_MN_CASE( mat_eval, dense_mat, 0, 1 );
	ADD_MN_CASE( mat_eval, dense_mat, 0, 5 );
	ADD_MN_CASE( mat_eval, dense_mat, 1, 0 );
	ADD_MN_CASE( mat_eval, dense_mat, 1, 1 );
	ADD_MN_CASE( mat_eval, dense_mat, 1, 5 );
	ADD_MN_CASE( mat_eval, dense_mat, 4, 0 );
	ADD_MN_CASE( mat_eval, dense_mat, 4, 1 );
	ADD_MN_CASE( mat_eval, dense_mat, 4, 5 );
END_TPACK

BEGIN_TPACK( ref_mat_eval )
	ADD_MN_CASE( mat_eval, ref_mat, 0, 0 );
	ADD_MN_CASE( mat_eval, ref_mat, 0, 1 );
	ADD_MN_CASE( mat_eval, ref_mat, 0, 5 );
	ADD_MN_CASE( mat_eval, ref_mat, 1, 0 );
	ADD_MN_CASE( mat_eval, ref_mat, 1, 1 );
	ADD_MN_CASE( mat_eval, ref_mat, 1, 5 );
	ADD_MN_CASE( mat_eval, ref_mat, 4, 0 );
	ADD_MN_CASE( mat_eval, ref_mat, 4, 1 );
	ADD_MN_CASE( mat_eval, ref_mat, 4, 5 );
END_TPACK

BEGIN_TPACK( ref_mat_ex_eval )
	ADD_MN_CASE( mat_eval, ref_mat_ex, 0, 0 );
	ADD_MN_CASE( mat_eval, ref_mat_ex, 0, 1 );
	ADD_MN_CASE( mat_eval, ref_mat_ex, 0, 5 );
	ADD_MN_CASE( mat_eval, ref_mat_ex, 1, 0 );
	ADD_MN_CASE( mat_eval, ref_mat_ex, 1, 1 );
	ADD_MN_CASE( mat_eval, ref_mat_ex, 1, 5 );
	ADD_MN_CASE( mat_eval, ref_mat_ex, 4, 0 );
	ADD_MN_CASE( mat_eval, ref_mat_ex, 4, 1 );
	ADD_MN_CASE( mat_eval, ref_mat_ex, 4, 5 );
END_TPACK

BEGIN_MAIN_SUITE
	ADD_TPACK( dense_mat_eval )
	ADD_TPACK( ref_mat_eval )
	ADD_TPACK( ref_mat_ex_eval )
END_MAIN_SUITE



