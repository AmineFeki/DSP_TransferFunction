# DSP_TransferFunction

This project is designed to allow users to implement any continuous transfer function (Laplace format) on the MCU. It converts the continuous function to the discrete one using one of the approximation algorithms (ZoH, Tustin, (etc.)), generates the recurring equation, and executes it. We can use this project either to generate signals, simulate them, and simulate digital filters.

## Discretize continuous transfer function:

Discretizing continuous functions is expressing the transfer function in the Z domain. Which means expressing the output at a discrete instant (which is multiple of the sampling period), with the input at the same and some previous instants, and some previous outputs.

This discrete function is at the origin of generating the recurring equation that will be implement on the MCU.

Discretizing the continuous transfer function uses different discretizing transformations, such as Zoh, Tustin, (etc.). It consists of replacing the term “p” of Laplace transformation by a specific term depending on the used discretizing transformation.

Let’s discover how to discretize using Tustin transformation!

Let

\(G(p) = {{1} \over {1+p^2}}\)

${G(p) = {{1} \over {1+p^2}}}$.



We finally obtain, 

${G(z)= {{{1} \over {1+4 \over {T_s^2} }} + {{2} \over {1+4 \over {T_s^2} }}.z^{-1} + {{1} \over {1+4 \over {T_s^2} }}.z^{-2} } \over { 1 +{{1 - 8 \over Ts^2}\over {1 + 4 \over Ts^2}}.z^-1 + z^-2}}$
