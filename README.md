
### Haku (WIP)
==== FAQ As ====
- Haku 
  - ... is a concord graph viewer, designed to be as minimal as possible.

  - ... is designed for messaging and plaintext protocols.

  - ... doesn't control any nodes. **Use of a node controller is highly recommended.**

  - ... is linux first. There's no intention to support Windows natively; use WSL. (Apple; use at own risk)


==== Usage ====
Haku uses a UNIX socket to 'communicate'. If you don't read it, haku will be screaming into the void :(.


==== Design ====
Initially (optimistically) designed to handle **all** possible protocols, haku was dramatically reduced in scope, to promote greater specialisation among tools.

Haku does no parsing, besides simple string searches to facilitate searching the message buffer.
