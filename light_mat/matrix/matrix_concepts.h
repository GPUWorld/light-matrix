/**
 * @file matrix_concepts.h
 *
 * Basic matrix concepts
 *
 * @author Dahua Lin
 */

#ifdef _MSC_VER
#pragma once
#endif

#ifndef LIGHTMAT_MATRIX_CONCEPTS_H_
#define LIGHTMAT_MATRIX_CONCEPTS_H_

#include <light_mat/matrix/matrix_meta.h>

#ifdef LMAT_ENABLE_INDEX_CHECKING
#define LMAT_CHECK_IDX(i, n) check_arg(i >= 0 && i < (n), "Index out of range.");
#define LMAT_CHECK_SUBS(a, i, j) \
		check_arg(i >= 0 && i < (a).nrows() && j >= 0 && j < (a).ncolumns(), "Subscripts out of range.");
#else
#define LMAT_CHECK_IDX(i, n)
#define LMAT_CHECK_SUBS(a, i, j)
#endif


namespace lmat
{

	/********************************************
	 *
	 *  IMatrixXpr
	 *
	 ********************************************/

	template<class Derived, typename T>
	class IMatrixXpr
	{
	public:
		LMAT_CRTP_REF

		LMAT_ENSURE_INLINE index_t nelems() const
		{
			return derived().nelems();
		}

		LMAT_ENSURE_INLINE index_t nrows() const
		{
			return derived().nrows();
		}

		LMAT_ENSURE_INLINE index_t ncolumns() const
		{
			return derived().ncolumns();
		}

		LMAT_ENSURE_INLINE typename meta::shape<Derived>::type
		shape() const
		{
			return derived().shape();
		}

	}; // end class IMatrixXpr


	template<class Derived>
	class matrix_xpr_base
	: public IMatrixXpr<Derived, typename meta::value_type_of<Derived>::type>
	{
	public:
		typedef typename meta::value_type_of<Derived>::type value_type;
		typedef typename meta::shape<Derived>::type shape_type;

	public:
		LMAT_ENSURE_INLINE
		matrix_xpr_base(index_t m, index_t n)
		: m_shape(m, n) { }

		LMAT_ENSURE_INLINE
		matrix_xpr_base(const shape_type& shape)
		: m_shape(shape) { }

		LMAT_ENSURE_INLINE index_t nelems() const
		{
			return m_shape.nelems();
		}

		LMAT_ENSURE_INLINE index_t nrows() const
		{
			return m_shape.nrows();
		}

		LMAT_ENSURE_INLINE index_t ncolumns() const
		{
			return m_shape.ncolumns();
		}

		LMAT_ENSURE_INLINE shape_type shape() const
		{
			return m_shape;
		}

	private:
		shape_type m_shape;
	};


	template<class Derived, class Arg>
	class sarg_matrix_xpr_base
	: public IMatrixXpr<Derived, typename meta::value_type_of<Derived>::type>
	{
	public:
		typedef typename meta::value_type_of<Derived>::type value_type;
		typedef typename meta::shape<Derived>::type shape_type;

	public:

		LMAT_ENSURE_INLINE
		sarg_matrix_xpr_base(const Arg& arg)
		: m_arg(arg) { }

		LMAT_ENSURE_INLINE const Arg& arg() const
		{
			return m_arg;
		}

		LMAT_ENSURE_INLINE index_t nelems() const
		{
			return m_arg.nelems();
		}

		LMAT_ENSURE_INLINE index_t nrows() const
		{
			return m_arg.nrows();
		}

		LMAT_ENSURE_INLINE index_t ncolumns() const
		{
			return m_arg.ncolumns();
		}

		LMAT_ENSURE_INLINE shape_type shape() const
		{
			return m_arg.shape();
		}

	private:
		const Arg& m_arg;
	};


	/********************************************
	 *
	 *  IEWiseMatrix
	 *
	 ********************************************/

	template<class Derived, typename T>
	class IEWiseMatrix : public IMatrixXpr<Derived, T> { };


	template<class Derived>
	class ewise_matrix_base
	: public IEWiseMatrix<Derived, typename meta::value_type_of<Derived>::type>
	{
	public:
		typedef typename meta::value_type_of<Derived>::type value_type;
		typedef typename meta::shape<Derived>::type shape_type;

	public:

		LMAT_ENSURE_INLINE
		ewise_matrix_base(index_t m, index_t n)
		: m_shape(m, n) { }

		LMAT_ENSURE_INLINE
		ewise_matrix_base(const shape_type& shape)
		: m_shape(shape) { }

		LMAT_ENSURE_INLINE index_t nelems() const
		{
			return m_shape.nelems();
		}

		LMAT_ENSURE_INLINE index_t nrows() const
		{
			return m_shape.nrows();
		}

		LMAT_ENSURE_INLINE index_t ncolumns() const
		{
			return m_shape.ncolumns();
		}

		LMAT_ENSURE_INLINE shape_type shape() const
		{
			return m_shape;
		}

	private:
		shape_type m_shape;
	};


	/********************************************
	 *
	 *  IRegularMatrix
	 *
	 ********************************************/

	template<class Derived, typename T>
	class IRegularMatrix : public IEWiseMatrix<Derived, T>
	{
	public:
		typedef typename meta::value_type_of<Derived>::type value_type;
		typedef typename meta::pointer_of<Derived>::type pointer;
		typedef typename meta::reference_of<Derived>::type reference;
		typedef typename meta::const_pointer_of<Derived>::type const_pointer;
		typedef typename meta::const_reference_of<Derived>::type const_reference;

		typedef typename meta::shape<Derived>::type shape_type;

	public:
		LMAT_CRTP_REF

		LMAT_ENSURE_INLINE index_t nelems() const
		{
			return derived().nelems();
		}

		LMAT_ENSURE_INLINE index_t nrows() const
		{
			return derived().nrows();
		}

		LMAT_ENSURE_INLINE index_t ncolumns() const
		{
			return derived().ncolumns();
		}

		LMAT_ENSURE_INLINE shape_type shape() const
		{
			return derived().shape();
		}

		LMAT_ENSURE_INLINE bool is_contiguous() const
		{
			return derived().is_contiguous();
		}

		LMAT_ENSURE_INLINE bool is_percol_contiguous() const
		{
			return derived().is_percol_contiguous();
		}

		LMAT_ENSURE_INLINE index_t row_stride() const
		{
			return derived().row_stride();
		}

		LMAT_ENSURE_INLINE index_t col_stride() const
		{
			return derived().col_stride();
		}

		LMAT_ENSURE_INLINE const_pointer ptr_data() const
		{
			return derived().ptr_data();
		}

		LMAT_ENSURE_INLINE pointer ptr_data()
		{
			return derived().ptr_data();
		}

		LMAT_ENSURE_INLINE const_pointer ptr_col(const index_t j) const
		{
			LMAT_CHECK_IDX(j, ncolumns())
			return derived().ptr_col(j);
		}

		LMAT_ENSURE_INLINE pointer ptr_col(const index_t j)
		{
			LMAT_CHECK_IDX(j, ncolumns())
			return derived().ptr_col(j);
		}

		LMAT_ENSURE_INLINE const_pointer ptr_row(const index_t i) const
		{
			LMAT_CHECK_IDX(i, nrows())
			return derived().ptr_row(i);
		}

		LMAT_ENSURE_INLINE pointer ptr_row(const index_t i)
		{
			LMAT_CHECK_IDX(i, nrows())
			return derived().ptr_row(i);
		}

		LMAT_ENSURE_INLINE const_reference elem(const index_t i, const index_t j) const
		{
			return derived().elem(i, j);
		}

		LMAT_ENSURE_INLINE reference elem(const index_t i, const index_t j)
		{
			return derived().elem(i, j);
		}

		LMAT_ENSURE_INLINE const_reference operator() (const index_t i, const index_t j) const
		{
			LMAT_CHECK_SUBS(*this, i, j)
			return elem(i, j);
		}

		LMAT_ENSURE_INLINE reference operator() (const index_t i, const index_t j)
		{
			LMAT_CHECK_SUBS(*this, i, j)
			return elem(i, j);
		}

		LMAT_ENSURE_INLINE void require_size(index_t m, index_t n)
		{
			derived().require_size(m, n);
		}

	public:

		// iteration

		LMAT_ENSURE_INLINE
		typename matrix_iter<Derived>::const_iterator begin() const
		{
			return matrix_iter<Derived>::begin(derived());
		}

		LMAT_ENSURE_INLINE
		typename matrix_iter<Derived>::const_iterator end() const
		{
			return matrix_iter<Derived>::end(derived());
		}

		LMAT_ENSURE_INLINE
		typename matrix_iter<Derived>::iterator begin()
		{
			return matrix_iter<Derived>::begin(derived());
		}

		LMAT_ENSURE_INLINE
		typename matrix_iter<Derived>::iterator end()
		{
			return matrix_iter<Derived>::end(derived());
		}

		LMAT_ENSURE_INLINE
		typename matrix_iter<Derived>::col_const_iterator col_begin(index_t j) const
		{
			return matrix_iter<Derived>::col_begin(derived(), j);
		}

		LMAT_ENSURE_INLINE
		typename matrix_iter<Derived>::col_const_iterator col_end(index_t j) const
		{
			return matrix_iter<Derived>::col_end(derived(), j);
		}

		LMAT_ENSURE_INLINE
		typename matrix_iter<Derived>::col_iterator col_begin(index_t j)
		{
			return matrix_iter<Derived>::col_begin(derived(), j);
		}

		LMAT_ENSURE_INLINE
		typename matrix_iter<Derived>::col_iterator col_end(index_t j)
		{
			return matrix_iter<Derived>::col_end(derived(), j);
		}


	public:

		// sub-vector views (only apply to compile-time vectors)

		template<class Range>
		LMAT_ENSURE_INLINE
		typename vecview_map<Derived, Range>::const_type
		operator() (const IRange<Range>& rgn) const
		{
			return vecview_map<Derived, Range>::get(derived(), rgn.derived());
		}

		template<class Range>
		LMAT_ENSURE_INLINE
		typename vecview_map<Derived, Range>::type
		operator() (const IRange<Range>& rgn)
		{
			return vecview_map<Derived, Range>::get(derived(), rgn.derived());
		}

		// column views

		LMAT_ENSURE_INLINE
		typename colview_map<Derived, whole>::const_type
		column(const index_t j) const
		{
			LMAT_CHECK_IDX(j, this->ncolumns())
			return colview_map<Derived, whole>::get(derived(), j, whole());
		}

		LMAT_ENSURE_INLINE
		typename colview_map<Derived, whole>::type
		column(const index_t j)
		{
			LMAT_CHECK_IDX(j, this->ncolumns())
			return colview_map<Derived, whole>::get(derived(), j, whole());
		}

		template<class Range>
		LMAT_ENSURE_INLINE
		typename colview_map<Derived, Range>::const_type
		operator()(const IRange<Range>& rgn, const index_t j) const
		{
			LMAT_CHECK_IDX(j, this->ncolumns())
			return colview_map<Derived, Range>::get(derived(), j, rgn.derived());
		}

		template<class Range>
		LMAT_ENSURE_INLINE
		typename colview_map<Derived, Range>::type
		operator()(const IRange<Range>& rgn, const index_t j)
		{
			LMAT_CHECK_IDX(j, this->ncolumns())
			return colview_map<Derived, Range>::get(derived(), j, rgn.derived());
		}

		// row views

		LMAT_ENSURE_INLINE
		typename rowview_map<Derived, whole>::const_type
		row(const index_t i) const
		{
			LMAT_CHECK_IDX(i, this->nrows())
			return rowview_map<Derived, whole>::get(derived(), i, whole());
		}

		LMAT_ENSURE_INLINE
		typename rowview_map<Derived, whole>::type
		row(const index_t i)
		{
			LMAT_CHECK_IDX(i, this->nrows())
			return rowview_map<Derived, whole>::get(derived(), i, whole());
		}

		template<class Range>
		LMAT_ENSURE_INLINE
		typename rowview_map<Derived, Range>::const_type
		operator()(const index_t i, const IRange<Range>& rgn) const
		{
			LMAT_CHECK_IDX(i, this->nrows())
			return rowview_map<Derived, Range>::get(derived(), i, rgn.derived());
		}

		template<class Range>
		LMAT_ENSURE_INLINE
		typename rowview_map<Derived, Range>::type
		operator()(const index_t i, const IRange<Range>& rgn)
		{
			LMAT_CHECK_IDX(i, this->nrows())
			return rowview_map<Derived, Range>::get(derived(), i, rgn.derived());
		}


		// mat-views

		template<class Range0, class Range1>
		LMAT_ENSURE_INLINE
		typename matview_map<Derived, Range0, Range1>::const_type
		operator()(const IRange<Range0>& row_rgn, const IRange<Range1>& col_rgn) const
		{
			return matview_map<Derived, Range0, Range1>::get(derived(),
					row_rgn.derived(), col_rgn.derived());
		}

		template<class Range0, class Range1>
		LMAT_ENSURE_INLINE
		typename matview_map<Derived, Range0, Range1>::type
		operator()(const IRange<Range0>& row_rgn, const IRange<Range1>& col_rgn)
		{
			return matview_map<Derived, Range0, Range1>::get(derived(),
					row_rgn.derived(), col_rgn.derived());
		}

		// diagonal view

		LMAT_ENSURE_INLINE
		typename diagview_map<Derived>::const_type diag() const
		{
			return diagview_map<Derived>::get(derived());
		}

		LMAT_ENSURE_INLINE
		typename diagview_map<Derived>::type diag()
		{
			return diagview_map<Derived>::get(derived());
		}

	}; // end class IRegularMatrix


	template<class Mat, typename T>
	LMAT_ENSURE_INLINE
	inline typename matrix_iter<Mat>::const_iterator
	begin(const IRegularMatrix<Mat, T>& mat)
	{
		return mat.begin();
	}

	template<class Mat, typename T>
	LMAT_ENSURE_INLINE
	inline typename matrix_iter<Mat>::const_iterator
	end(const IRegularMatrix<Mat, T>& mat)
	{
		return mat.end();
	}

	template<class Mat, typename T>
	LMAT_ENSURE_INLINE
	inline typename matrix_iter<Mat>::iterator
	begin(IRegularMatrix<Mat, T>& mat)
	{
		return mat.begin();
	}

	template<class Mat, typename T>
	LMAT_ENSURE_INLINE
	inline typename matrix_iter<Mat>::iterator
	end(IRegularMatrix<Mat, T>& mat)
	{
		return mat.end();
	}


}

#endif /* MATRIX_CONCEPTS_H_ */


