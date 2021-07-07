#include <pybind11/pybind11.h>
#include <pybind11/eigen.h>

#include <ipc/distance/edge_edge_mollifier.hpp>

#include "../utils.hpp"

namespace py = pybind11;
using namespace ipc;

void define_edge_edge_mollifier_functions(py::module_& m)
{
    m.def(
        "edge_edge_cross_squarednorm",
        [](const Eigen::Vector3d& ea0, const Eigen::Vector3d& ea1,
           const Eigen::Vector3d& eb0, const Eigen::Vector3d& eb1) {
            return edge_edge_cross_squarednorm(ea0, ea1, eb0, eb1);
        },
        R"ipc_Qu8mg5v7(
        Compute the squared norm of the edge-edge cross product.

        Parameters
        ----------
        ea0 : The first vertex of the first edge
        ea1 : The second vertex of the first edge
        eb0 : The first vertex of the second edge
        eb1 : The second vertex of the second edge

        Returns
        -------
        The squared norm of the edge-edge cross product.
        )ipc_Qu8mg5v7",
        py::arg("ea0"), py::arg("ea1"), py::arg("eb0"), py::arg("eb1"));

    m.def(
        "edge_edge_cross_squarednorm_gradient",
        [](const Eigen::Vector3d& ea0, const Eigen::Vector3d& ea1,
           const Eigen::Vector3d& eb0, const Eigen::Vector3d& eb1) {
            Vector<double, 12> grad;
            edge_edge_cross_squarednorm_gradient(ea0, ea1, eb0, eb1, grad);
            return grad;
        },
        R"ipc_Qu8mg5v7(
        Compute the gradient of the squared norm of the edge cross product.

        Parameters
        ----------
        ea0 : The first vertex of the first edge
        ea1 : The second vertex of the first edge
        eb0 : The first vertex of the second edge
        eb1 : The second vertex of the second edge

        Returns
        -------
        The gradient of the squared norm of the edge cross product wrt ea0, ea1, eb0, and eb1.
        )ipc_Qu8mg5v7",
        py::arg("ea0"), py::arg("ea1"), py::arg("eb0"), py::arg("eb1"));

    m.def(
        "edge_edge_cross_squarednorm_hessian",
        [](const Eigen::Vector3d& ea0, const Eigen::Vector3d& ea1,
           const Eigen::Vector3d& eb0, const Eigen::Vector3d& eb1) {
            Eigen::Matrix<double, 12, 12> hess;
            edge_edge_cross_squarednorm_hessian(ea0, ea1, eb0, eb1, hess);
            return hess;
        },
        R"ipc_Qu8mg5v7(
        Compute the hessian of the squared norm of the edge cross product.

        Parameters
        ----------
        ea0 : The first vertex of the first edge
        ea1 : The second vertex of the first edge
        eb0 : The first vertex of the second edge
        eb1 : The second vertex of the second edge

        Returns
        -------
        The hessian of the squared norm of the edge cross product wrt ea0, ea1, eb0, and eb1.
        )ipc_Qu8mg5v7",
        py::arg("ea0"), py::arg("ea1"), py::arg("eb0"), py::arg("eb1"));

    m.def(
        "edge_edge_mollifier", &edge_edge_mollifier<double>,
        R"ipc_Qu8mg5v7(
        Mollifier function for edge-edge distance.

        Parameters
        ----------
        x : Squared norm of the edge-edge cross product
        eps_x : Mollifier activation threshold.

        Returns
        -------
        The mollifier coefficient to premultiply the edge-edge distance.
        )ipc_Qu8mg5v7",
        py::arg("x"), py::arg("eps_x"));

    m.def(
        "edge_edge_mollifier", &edge_edge_mollifier_gradient<double>,
        R"ipc_Qu8mg5v7(
        The gradient of the mollifier function for edge-edge distance.

        Parameters
        ----------
        x : Squared norm of the edge-edge cross product
        eps_x : Mollifier activation threshold.

        Returns
        -------
        The gradient of the mollifier function for edge-edge distance wrt x.
        )ipc_Qu8mg5v7",
        py::arg("x"), py::arg("eps_x"));

    m.def(
        "edge_edge_mollifier", &edge_edge_mollifier_hessian<double>,
        R"ipc_Qu8mg5v7(
        The hessian of the mollifier function for edge-edge distance.

        Parameters
        ----------
        x : Squared norm of the edge-edge cross product
        eps_x : Mollifier activation threshold.

        Returns
        -------
        The hessian of the mollifier function for edge-edge distance wrt x.
        )ipc_Qu8mg5v7",
        py::arg("x"), py::arg("eps_x"));

    m.def(
        "edge_edge_mollifier_threshold",
        [](const Eigen::Vector3d& ea0_rest, const Eigen::Vector3d& ea1_rest,
           const Eigen::Vector3d& eb0_rest, const Eigen::Vector3d& eb1_rest) {
            return edge_edge_mollifier_threshold(
                ea0_rest, ea1_rest, eb0_rest, eb1_rest);
        },
        R"ipc_Qu8mg5v7(
        Compute the threshold of the mollifier edge-edge distance.

        This values is computed based on the edges at rest length.

        Parameters
        ----------
        x : Squared norm of the edge-edge cross product
        eps_x : Mollifier activation threshold.

        Returns
        -------
        Threshold for edge-edge mollification.
        )ipc_Qu8mg5v7",
        py::arg("ea0_rest"), py::arg("ea1_rest"), py::arg("eb0_rest"),
        py::arg("eb1_rest"));
}
