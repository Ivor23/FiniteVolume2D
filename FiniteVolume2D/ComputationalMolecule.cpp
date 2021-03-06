#include "ComputationalMolecule.h"

#include "FluxComputationalMolecule.h"


ComputationalMolecule::ComputationalMolecule()
    :
    ComputationalMoleculeImpl("undef") {}

ComputationalMolecule::ComputationalMolecule(std::string const & var_name)
    :
    ComputationalMoleculeImpl(var_name) {}

bool
ComputationalMolecule::addMolecule(FluxComputationalMolecule const & in) {
    return in.addMolecule(*this);
}

void
ComputationalMolecule::setValue(double value) {
    value_ = value;
}

double
ComputationalMolecule::getValue() const {
    return value_;
}
