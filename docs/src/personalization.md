# Personalization

Some commands are enabled during the personalization phase in order to configure certain parameters of the Smart Card, such as the PIN and the ATR.

These commands are available from the moment the `init` command is received and until the `finish` command is received, which sets the card state to (_TODO_).

## `init` command

The `init` command is used to initialize the Smart Card. After this command all the personalization commands are available.
