type messageType = [ | `success | `error];

type notification = {
  id: float,
  message: React.element,
  type_: messageType,
};

type t = {
  show: (messageType, string) => unit,
  notifications: array(notification),
};

let initialState = {show: (_, _) => (), notifications: [||]};

let context = React.createContext(initialState);

let makeProps = (~value, ~children, ()) => {
  "value": value,
  "children": children,
};

let make = React.Context.provider(context);