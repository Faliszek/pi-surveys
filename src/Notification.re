open NotificationContext;

let use = () => React.useContext(context);

module Provider = {
  [@react.component]
  let make = (~children, ~value) => {
    Js.log2(children, value);

    <NotificationContext value> children </NotificationContext>;
  };
};