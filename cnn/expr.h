#ifndef EXPR_H
#define EXPR_H

#include "cnn/cnn.h"
#include "cnn/nodes.h"

namespace cnn { namespace expr {

struct Expression {
  ComputationGraph *pg;
  VariableIndex i;

  Expression() : pg(nullptr) { }
  Expression(ComputationGraph *pg, VariableIndex i) : pg(pg), i(i) { }
};

Expression input(ComputationGraph& g, real s);
Expression input(ComputationGraph& g, const real *ps);
Expression input(ComputationGraph& g, const Dim& d, const std::vector<float>* pdata);
Expression parameter(ComputationGraph& g, Parameters* p);
Expression lookup(ComputationGraph& g, LookupParameters* p, unsigned index);
Expression lookup(ComputationGraph& g, LookupParameters* p, const unsigned* pindex);

Expression operator-(const Expression& x);
Expression operator+(const Expression& x, const Expression& y);
//Expression operator+(const Expression& x, real y);
Expression operator-(const Expression& x, const Expression& y);
Expression operator-(const Expression& x, real y);
Expression operator*(const Expression& x, const Expression& y);
//Expression cwiseMultiply(const Expression& x, const Expression& y);

Expression tanh(const Expression& x);
Expression log(const Expression& x);
Expression logistic(const Expression& x);
Expression rectify(const Expression& x);
Expression log_softmax(const Expression& x);
Expression softmax(const Expression& x);

Expression cwise_multiply(const Expression& x, const Expression& y);

Expression squaredDistance(const Expression& x, const Expression& y);
Expression binary_log_loss(const Expression& x, real ty);
Expression binary_log_loss(const Expression& x, real* pty);
Expression pairwise_rank_loss(const Expression& x, const Expression& y, real m=1.0);

Expression pick(const Expression& x, unsigned v);
Expression pick(const Expression& x, unsigned* pv);
Expression pickrange(const Expression& x, unsigned v, unsigned u);

Expression pickneglogsoftmax(const Expression& x, unsigned v);

template <typename T>
Expression sum(const T& xs) {
  ComputationGraph *pg = xs.begin()->pg;
  std::vector<VariableIndex> xis(xs.size());
  for (int i=0; i<xs.size(); ++i) xis[i] = xs[i].i;
  return Expression(pg, pg->add_function<Sum>(xis));
}

template <typename T>
Expression concatenate_cols(const T& xs) {
  ComputationGraph *pg = xs.begin()->pg;
  std::vector<VariableIndex> xis(xs.size());
  for (int i=0; i<xs.size(); ++i) xis[i] = xs[i].i;
  return Expression(pg, pg->add_function<ConcatenateColumns>(xis));
}

template <typename T>
Expression concatenate(const T& xs) {
  ComputationGraph *pg = xs.begin()->pg;
  std::vector<VariableIndex> xis(xs.size());
  for (int i=0; i<xs.size(); ++i) xis[i] = xs[i].i;
  return Expression(pg, pg->add_function<Concatenate>(xis));
}

Expression sum_cols(const Expression& x);

Expression kmh_ngram(const Expression& x, unsigned n);

} }

#endif
